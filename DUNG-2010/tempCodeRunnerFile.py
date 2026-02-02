import tkinter as tk
from tkinter import ttk, messagebox, filedialog
import os
import sys
import threading
import time
import json
import subprocess # Thư viện để chạy lệnh hệ thống (pdflatex)
from datetime import datetime

# Import các thư viện cần thiết
try:
    from groq import Groq
    # Bỏ fpdf vì chuyển sang dùng LaTeX
    # Thêm thư viện đọc file
    import docx  # python-docx
    from pypdf import PdfReader # pypdf
except ImportError:
    print("Thiếu thư viện! Vui lòng chạy: pip install groq python-docx pypdf")
    sys.exit()

CONFIG_FILE = "config.json"
# Model AI được sử dụng
AI_MODEL = "openai/gpt-oss-120b" 

class ExamGeneratorApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Hệ Thống Luyện Đề HSG Tin Học (LaTeX Edition) - Cho Việt Dũng Đẹp Zai")
        self.root.geometry("750x700")
        
        # Style
        style = ttk.Style()
        style.theme_use('clam')
        
        # --- Variables ---
        self.api_key_var = tk.StringVar()
        self.matrix_path_var = tk.StringVar()
        self.output_dir_var = tk.StringVar()
        self.quantity_var = tk.IntVar(value=1)
        
        # Biến lưu trữ nội dung ma trận
        self.raw_matrix_content = ""
        self.optimized_matrix_content = ""
        self.use_optimized_var = tk.StringVar(value="Gốc") # Gốc hoặc Tối ưu

        # --- UI Layout ---
        main_frame = ttk.Frame(root, padding="20")
        main_frame.pack(fill=tk.BOTH, expand=True)

        # Title
        lbl_title = ttk.Label(main_frame, text="AUTO GENERATOR ĐỀ TIN HỌC (LATEX -> PDF)", font=("Helvetica", 14, "bold"))
        lbl_title.pack(pady=10)

        # 1. Configuration Section
        config_frame = ttk.LabelFrame(main_frame, text="Cấu hình hệ thống", padding="10")
        config_frame.pack(fill=tk.X, pady=5)
        
        # API Key
        ttk.Label(config_frame, text="Groq API Key:").grid(row=0, column=0, sticky=tk.W, pady=5)
        self.ent_api = ttk.Entry(config_frame, textvariable=self.api_key_var, show="*", width=50)
        self.ent_api.grid(row=0, column=1, padx=5, pady=5, columnspan=2)

        # 2. Input Data Section (Matrix)
        input_frame = ttk.LabelFrame(main_frame, text="Phân tích Ma trận (Word/PDF)", padding="10")
        input_frame.pack(fill=tk.X, pady=5)

        # Matrix File Selection
        ttk.Label(input_frame, text="File Ma Trận:").grid(row=0, column=0, sticky=tk.W, pady=5)
        self.ent_matrix = ttk.Entry(input_frame, textvariable=self.matrix_path_var, width=40, state='readonly')
        self.ent_matrix.grid(row=0, column=1, padx=5, pady=5)
        ttk.Button(input_frame, text="Chọn File", command=self.browse_matrix_file).grid(row=0, column=2, padx=5)
        
        # Nút Phân tích & Dropdown
        action_sub_frame = ttk.Frame(input_frame)
        action_sub_frame.grid(row=1, column=0, columnspan=3, sticky=tk.W, pady=10)
        
        self.btn_analyze = ttk.Button(action_sub_frame, text="PHÂN TÍCH & TỐI ƯU TOKEN", command=self.start_analyze_matrix)
        self.btn_analyze.pack(side=tk.LEFT, padx=5)
        
        ttk.Label(action_sub_frame, text="Chọn nguồn dữ liệu:").pack(side=tk.LEFT, padx=10)
        self.cbo_source = ttk.Combobox(action_sub_frame, textvariable=self.use_optimized_var, state="readonly", width=30)
        self.cbo_source['values'] = ("Dữ liệu Gốc (Chưa phân tích)",)
        self.cbo_source.current(0)
        self.cbo_source.pack(side=tk.LEFT, padx=5)

        # 3. Output Configuration
        output_frame = ttk.LabelFrame(main_frame, text="Cấu hình xuất bản", padding="10")
        output_frame.pack(fill=tk.X, pady=5)

        # Output Directory
        ttk.Label(output_frame, text="Thư mục lưu đề:").grid(row=0, column=0, sticky=tk.W, pady=5)
        self.ent_out = ttk.Entry(output_frame, textvariable=self.output_dir_var, width=40, state='readonly')
        self.ent_out.grid(row=0, column=1, padx=5, pady=5)
        ttk.Button(output_frame, text="Chọn Folder", command=self.browse_output_dir).grid(row=0, column=2, padx=5)

        # Quantity
        ttk.Label(output_frame, text="Số lượng đề cần tạo:").grid(row=1, column=0, sticky=tk.W, pady=5)
        self.spin_qty = ttk.Spinbox(output_frame, from_=1, to=100, textvariable=self.quantity_var, width=10)
        self.spin_qty.grid(row=1, column=1, sticky=tk.W, padx=5, pady=5)

        # 4. Action Section
        btn_frame = ttk.Frame(main_frame)
        btn_frame.pack(pady=15)
        
        self.btn_generate = ttk.Button(btn_frame, text="BẮT ĐẦU TẠO HÀNG LOẠT", command=self.start_batch_generation)
        self.btn_generate.pack(side=tk.LEFT, padx=10, ipadx=10, ipady=5)
        
        # 5. Log Area
        log_frame = ttk.LabelFrame(main_frame, text="Tiến trình xử lý", padding="10")
        log_frame.pack(fill=tk.BOTH, expand=True, pady=5)
        
        self.log_text = tk.Text(log_frame, height=10, state='disabled', font=("Consolas", 9))
        self.log_text.pack(fill=tk.BOTH, expand=True)

        # --- Load Config on Start ---
        self.load_config()
        self.check_latex_installed()

    def log(self, message):
        self.log_text.config(state='normal')
        self.log_text.insert(tk.END, f"[{datetime.now().strftime('%H:%M:%S')}] {message}\n")
        self.log_text.see(tk.END)
        self.log_text.config(state='disabled')

    def check_latex_installed(self):
        """Kiểm tra xem pdflatex có trong máy không"""
        try:
            subprocess.run(["pdflatex", "--version"], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            self.log("Đã tìm thấy LaTeX (pdflatex). Sẵn sàng tạo PDF!")
        except FileNotFoundError:
            self.log("CẢNH BÁO: Không tìm thấy 'pdflatex'. Vui lòng cài đặt MiKTeX hoặc TeX Live.")
            messagebox.showwarning("Thiếu LaTeX", "Hệ thống không tìm thấy 'pdflatex'.\nBạn chỉ có thể tạo file .tex, không thể tự nén sang PDF.")

    def load_config(self):
        """Tải cấu hình từ file JSON (bao gồm cả dữ liệu đã phân tích)"""
        if os.path.exists(CONFIG_FILE):
            try:
                with open(CONFIG_FILE, 'r', encoding='utf-8') as f:
                    config = json.load(f)
                    self.api_key_var.set(config.get('api_key', ''))
                    self.matrix_path_var.set(config.get('matrix_path', ''))
                    self.output_dir_var.set(config.get('output_dir', ''))
                    
                    # Tải dữ liệu tối ưu nếu có
                    saved_optimized = config.get('optimized_content', '')
                    if saved_optimized:
                        self.optimized_matrix_content = saved_optimized
                        self.cbo_source['values'] = ("Dữ liệu Gốc (Nặng Token)", "Dữ liệu Tối ưu (Đã lưu)")
                        self.cbo_source.current(1)
                        self.log("Đã tải dữ liệu phân tích cũ thành công.")
                    else:
                        self.log("Đã tải cấu hình (Chưa có dữ liệu phân tích).")
                        
            except Exception as e:
                self.log(f"Lỗi tải cấu hình: {e}")

    def save_config(self):
        """Lưu cấu hình hiện tại và dữ liệu đã phân tích"""
        config = {
            'api_key': self.api_key_var.get(),
            'matrix_path': self.matrix_path_var.get(),
            'output_dir': self.output_dir_var.get(),
            'optimized_content': self.optimized_matrix_content # Lưu nội dung đã phân tích
        }
        try:
            with open(CONFIG_FILE, 'w', encoding='utf-8') as f:
                json.dump(config, f, ensure_ascii=False, indent=4)
        except Exception as e:
            self.log(f"Không lưu được cấu hình: {e}")

    def browse_matrix_file(self):
        filetypes = [("Tài liệu Word", "*.docx"), ("Tài liệu PDF", "*.pdf"), ("File văn bản", "*.txt"), ("Tất cả file", "*.*")]
        filename = filedialog.askopenfilename(filetypes=filetypes)
        if filename:
            self.matrix_path_var.set(filename)
            self.cbo_source['values'] = ("Dữ liệu Gốc (File mới)",)
            self.cbo_source.current(0)
            self.save_config()

    def browse_output_dir(self):
        dirname = filedialog.askdirectory()
        if dirname:
            self.output_dir_var.set(dirname)
            self.save_config()

    def read_matrix_content(self, path):
        try:
            ext = os.path.splitext(path)[1].lower()
            content = ""
            if ext == ".txt":
                with open(path, "r", encoding="utf-8") as f: content = f.read()
            elif ext == ".docx":
                doc = docx.Document(path)
                content = "\n".join([para.text for para in doc.paragraphs])
            elif ext == ".pdf":
                reader = PdfReader(path)
                content = "\n".join([page.extract_text() for page in reader.pages])
            else:
                return None, "Định dạng file không hỗ trợ"
            return content, None
        except Exception as e:
            return None, str(e)

    def start_analyze_matrix(self):
        api_key = self.api_key_var.get().strip()
        matrix_path = self.matrix_path_var.get()
        
        if not api_key:
            messagebox.showerror("Lỗi", "Cần API Key để phân tích!")
            return
        if not matrix_path or not os.path.exists(matrix_path):
            messagebox.showerror("Lỗi", "Chưa chọn file ma trận hợp lệ!")
            return

        self.btn_analyze.config(state='disabled')
        threading.Thread(target=self.process_analysis, args=(api_key, matrix_path)).start()

    def process_analysis(self, api_key, matrix_path):
        try:
            self.log("Đang đọc file ma trận...")
            content, error = self.read_matrix_content(matrix_path)
            if error:
                self.log(f"Lỗi đọc file: {error}")
                return

            self.raw_matrix_content = content
            self.log(f"Đã đọc file ({len(content)} ký tự). Đang gửi AI tối ưu...")

            client = Groq(api_key=api_key)
            prompt = f"""
            Hãy đóng vai trò là một trợ lý phân tích đề thi.
            Dưới đây là nội dung thô của một file Ma trận/Đề cương ôn tập Tin học:
            ---
            {content[:15000]} 
            ---
            NHIỆM VỤ: Hãy tóm tắt lại cấu trúc đề thi một cách ngắn gọn, súc tích nhất để làm đầu vào cho prompt tạo đề sau này.
            Chỉ giữ lại: Các dạng bài toán, Thang điểm, Giới hạn.
            Kết quả trả về phải là Tiếng Việt.
            """
            
            completion = client.chat.completions.create(
                messages=[{"role": "user", "content": prompt}],
                model=AI_MODEL,
            )
            
            optimized = completion.choices[0].message.content
            self.optimized_matrix_content = optimized
            
            self.save_config()
            
            self.root.after(0, lambda: self.update_ui_after_analysis(True))
            self.log("Phân tích & Tối ưu thành công! Đã lưu vào cấu hình.")
            
        except Exception as e:
            self.log(f"Lỗi phân tích: {e}")
            self.root.after(0, lambda: self.update_ui_after_analysis(False))
        finally:
            self.btn_analyze.config(state='normal')

    def update_ui_after_analysis(self, success):
        if success:
            self.cbo_source['values'] = ("Dữ liệu Gốc (Nặng Token)", "Dữ liệu Tối ưu (Đã lưu)")
            self.cbo_source.current(1)
            messagebox.showinfo("Xong", "Đã phân tích xong và lưu lại! Lần sau chỉ cần chọn từ Dropdown.")
        else:
            self.cbo_source['values'] = ("Dữ liệu Gốc (Mặc định)",)
            self.cbo_source.current(0)

    def start_batch_generation(self):
        api_key = self.api_key_var.get().strip()
        out_dir = self.output_dir_var.get().strip()
        self.save_config() 

        if not api_key:
            messagebox.showerror("Thiếu thông tin", "Vui lòng nhập Groq API Key!")
            return
        if not out_dir:
            messagebox.showerror("Thiếu thông tin", "Vui lòng chọn thư mục lưu đề thi!")
            return

        self.btn_generate.config(state='disabled')
        qty = self.quantity_var.get()
        
        selection = self.cbo_source.get()
        final_matrix_context = ""
        
        if "Tối ưu" in selection and self.optimized_matrix_content:
            final_matrix_context = self.optimized_matrix_content
            self.log("Đang sử dụng: MA TRẬN ĐÃ TỐI ƯU")
        elif self.raw_matrix_content:
            final_matrix_context = self.raw_matrix_content
            self.log("Đang sử dụng: MA TRẬN GỐC TỪ FILE")
        else:
            path = self.matrix_path_var.get()
            if path and os.path.exists(path):
                content, err = self.read_matrix_content(path)
                if not err:
                    final_matrix_context = content
            if not final_matrix_context:
                final_matrix_context = "Cấu trúc chuẩn HSG Tin học: 3-4 bài toán lập trình."

        thread = threading.Thread(target=self.process_batch, args=(api_key, out_dir, qty, final_matrix_context))
        thread.start()

    def process_batch(self, api_key, out_dir, quantity, matrix_context):
        try:
            client = Groq(api_key=api_key)
            self.log(f"Bắt đầu tạo {quantity} đề thi (Chế độ LaTeX)...")

            for i in range(1, quantity + 1):
                self.log(f"--- Đang xử lý đề số {i}/{quantity} ---")
                
                # Prompt yêu cầu trả về LaTeX code chuẩn
                prompt = f"""
                Bạn là chuyên gia soạn thảo LaTeX và ra đề thi Tin học.
                Hãy tạo code LaTeX hoàn chỉnh cho ĐỀ THI HSG TIN HỌC LỚP 11 - ĐỀ SỐ {i}.
                
                CẤU TRÚC FORMAT ĐỀ THI CHUẨN (BẮT BUỘC):
                1. Header trái: SỞ GIÁO DỤC VÀ ĐÀO TẠO [TÊN TỈNH] (In đậm)
                2. Header phải: KỲ THI CHỌN HỌC SINH GIỎI CẤP TỈNH (In đậm) / Môn thi: TIN HỌC / Thời gian: 180 phút
                3. Bên dưới Header có dòng kẻ ngang và phần điền thông tin thí sinh: "Họ và tên thí sinh: ..................... Số báo danh: ....................."
                
                YÊU CẦU NỘI DUNG:
                - Chỉ bao gồm 3-4 bài toán lập trình (Tên bài, Đề bài, Input/Output, Ví dụ, Giới hạn).
                - Dựa trên ma trận:
                \"\"\"
                {matrix_context[:8000]}
                \"\"\"
                
                QUAN TRỌNG: 
                - KHÔNG ĐƯỢC SINH ĐÁP ÁN HAY CODE GIẢI Ở CUỐI ĐỀ. ĐÂY LÀ ĐỀ BÀI CHO HỌC SINH.
                - Sử dụng gói `vietnamese` babel.
                - Output code LaTeX raw, bắt đầu bằng \\documentclass.
                """

                try:
                    chat_completion = client.chat.completions.create(
                        messages=[
                            {"role": "system", "content": "Bạn là máy tạo đề thi LaTeX. Chỉ trả về raw code LaTeX. Không trả lời gì thêm."},
                            {"role": "user", "content": prompt}
                        ],
                        model=AI_MODEL,
                        temperature=0.7,
                    )
                    content = chat_completion.choices[0].message.content
                    
                    # Lọc sạch response để chỉ lấy code LaTeX
                    if "```latex" in content:
                        content = content.split("```latex")[1].split("```")[0]
                    elif "```" in content:
                        content = content.split("```")[1]
                    
                    content = content.strip()

                    # 1. Lưu file .tex
                    tex_filename = f"De_Tin_Hoc_So_{i:02d}.tex"
                    tex_path = os.path.join(out_dir, tex_filename)
                    
                    with open(tex_path, "w", encoding="utf-8") as f:
                        f.write(content)
                    
                    self.log(f"-> Đã sinh code LaTeX: {tex_filename}")

                    # 2. Biên dịch sang PDF (pdflatex)
                    try:
                        self.log("-> Đang nén PDF (pdflatex)...")
                        # Sử dụng cwd để chạy ngay tại thư mục đích
                        process = subprocess.run(
                            ["pdflatex", "-interaction=nonstopmode", tex_filename],
                            cwd=out_dir,
                            stdout=subprocess.DEVNULL, # Ẩn log rác
                            stderr=subprocess.PIPE
                        )
                        
                        if process.returncode == 0:
                            self.log(f"-> THÀNH CÔNG: Đã tạo file PDF cho đề số {i}")
                            # Dọn dẹp file rác (.aux, .log, .out) - CLEAR LOG THỪA
                            for ext in ['.aux', '.log', '.out', '.toc', '.snm', '.nav']:
                                junk_file = os.path.join(out_dir, f"De_Tin_Hoc_So_{i:02d}{ext}")
                                if os.path.exists(junk_file):
                                    try:
                                        os.remove(junk_file)
                                    except OSError:
                                        pass
                        else:
                            self.log(f"-> LỖI BIÊN DỊCH: Mã lỗi {process.returncode}. Kiểm tra file .log trong thư mục.")
                            
                    except FileNotFoundError:
                        self.log("-> LỖI: Không tìm thấy 'pdflatex'. File .tex vẫn được giữ lại.")
                    except Exception as e:
                         self.log(f"-> Lỗi khi chạy pdflatex: {e}")

                    time.sleep(1)

                except Exception as e:
                    self.log(f"Lỗi khi tạo đề {i}: {str(e)}")
            
            self.log("HOÀN TẤT TOÀN BỘ QUÁ TRÌNH!")
            messagebox.showinfo("Thành công", f"Kiểm tra thư mục:\n{out_dir}")

        except Exception as e:
            self.log(f"Lỗi hệ thống: {str(e)}")
            messagebox.showerror("Lỗi", str(e))
        finally:
            self.btn_generate.config(state='normal')

if __name__ == "__main__":
    root = tk.Tk()
    app = ExamGeneratorApp(root)
    root.mainloop()