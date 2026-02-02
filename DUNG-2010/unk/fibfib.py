"""
Thư viện Toán học - Number Theory & Algebra Library
Bao gồm: Số nguyên tố, ước số, bội số, UCLN, BCNN, phương trình, bất phương trình
"""

import math
from typing import List, Tuple, Set, Union
from fractions import Fraction


# ============= SỐ NGUYÊN TỐ =============

def la_so_nguyen_to(n: int) -> bool:
    """
    Kiểm tra n có phải số nguyên tố không
    
    Args:
        n: Số cần kiểm tra
    Returns:
        True nếu n là số nguyên tố, False nếu không
    """
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        if n % i == 0:
            return False
    return True
def iprm(n):
    if n<2:
        return False
    for i in range(2,int(math.sqrt(n))+1):
        if n% i ==0:
            return False
    return True

def sang_nguyen_to(n: int) -> List[int]:
    """
    Sàng Eratosthenes - Tìm tất cả số nguyên tố <= n
    
    Args:
        n: Giới hạn trên
    Returns:
        Danh sách các số nguyên tố từ 2 đến n
    """
    if n < 2:
        return []
    
    la_nguyen_to = [True] * (n + 1)
    la_nguyen_to[0] = la_nguyen_to[1] = False
    
    for i in range(2, int(math.sqrt(n)) + 1):
        if la_nguyen_to[i]:
            for j in range(i * i, n + 1, i):
                la_nguyen_to[j] = False
    
    return [i for i in range(n + 1) if la_nguyen_to[i]]


def n_so_nguyen_to_dau_tien(n: int) -> List[int]:
    """
    Tìm n số nguyên tố đầu tiên
    
    Args:
        n: Số lượng số nguyên tố cần tìm
    Returns:
        Danh sách n số nguyên tố đầu tiên
    """
    primes = []
    num = 2
    while len(primes) < n:
        if la_so_nguyen_to(num):
            primes.append(num)
        num += 1
    return primes


# ============= ƯỚC SỐ =============

def tim_uoc_so(n: int) -> List[int]:
    """
    Tìm tất cả ước số của n
    
    Args:
        n: Số cần tìm ước
    Returns:
        Danh sách các ước số của n (đã sắp xếp)
    """
    if n == 0:
        return []
    
    n = abs(n)
    uoc = []
    
    for i in range(1, int(math.sqrt(n)) + 1):
        if n % i == 0:
            uoc.append(i)
            if i != n // i:
                uoc.append(n // i)
    
    return sorted(uoc)


def dem_uoc_so(n: int) -> int:
    """
    Đếm số lượng ước số của n
    
    Args:
        n: Số cần đếm ước
    Returns:
        Số lượng ước số
    """
    return len(tim_uoc_so(n))


def tong_uoc_so(n: int) -> int:
    """
    Tính tổng các ước số của n
    
    Args:
        n: Số cần tính tổng ước
    Returns:
        Tổng các ước số
    """
    return sum(tim_uoc_so(n))


# ============= BỘI SỐ =============

def tim_boi_so(n: int, so_luong: int) -> List[int]:
    """
    Tìm các bội số của n
    
    Args:
        n: Số cần tìm bội
        so_luong: Số lượng bội số cần tìm
    Returns:
        Danh sách các bội số
    """
    return [n * i for i in range(1, so_luong + 1)]


def co_phai_boi_so(a: int, b: int) -> bool:
    """
    Kiểm tra a có phải bội số của b không
    
    Args:
        a: Số cần kiểm tra
        b: Số chia
    Returns:
        True nếu a là bội của b
    """
    if b == 0:
        return False
    return a % b == 0


# ============= ƯỚC CHUNG LỚN NHẤT (UCLN/GCD) =============

def ucln(a: int, b: int) -> int:
    """
    Tìm ước chung lớn nhất của a và b (thuật toán Euclid)
    
    Args:
        a, b: Hai số cần tìm UCLN
    Returns:
        UCLN của a và b
    """
    a, b = abs(a), abs(b)
    while b:
        a, b = b, a % b
    return a


def ucln_nhieu_so(*args: int) -> int:
    """
    Tìm UCLN của nhiều số
    
    Args:
        *args: Các số cần tìm UCLN
    Returns:
        UCLN của tất cả các số
    """
    if len(args) == 0:
        return 0
    
    result = abs(args[0])
    for num in args[1:]:
        result = ucln(result, abs(num))
        if result == 1:
            return 1
    return result


# ============= BỘI CHUNG NHỎ NHẤT (BCNN/LCM) =============

def bcnn(a: int, b: int) -> int:
    """
    Tìm bội chung nhỏ nhất của a và b
    
    Args:
        a, b: Hai số cần tìm BCNN
    Returns:
        BCNN của a và b
    """
    if a == 0 or b == 0:
        return 0
    return abs(a * b) // ucln(a, b)


def bcnn_nhieu_so(*args: int) -> int:
    """
    Tìm BCNN của nhiều số
    
    Args:
        *args: Các số cần tìm BCNN
    Returns:
        BCNN của tất cả các số
    """
    if len(args) == 0:
        return 0
    
    result = abs(args[0])
    for num in args[1:]:
        result = bcnn(result, abs(num))
    return result


# ============= PHÂN TÍCH THỪA SỐ NGUYÊN TỐ =============

def phan_tich_thua_so_nguyen_to(n: int) -> List[Tuple[int, int]]:
    """
    Phân tích n ra thừa số nguyên tố
    
    Args:
        n: Số cần phân tích
    Returns:
        Danh sách các tuple (thừa số, số mũ)
    
    Ví dụ: 
        phan_tich_thua_so_nguyen_to(60) = [(2, 2), (3, 1), (5, 1)]
        nghĩa là 60 = 2^2 × 3^1 × 5^1
    """
    if n < 2:
        return []
    
    n = abs(n)
    thua_so = []
    
    # Kiểm tra chia hết cho 2
    if n % 2 == 0:
        count = 0
        while n % 2 == 0:
            count += 1
            n //= 2
        thua_so.append((2, count))
    
    # Kiểm tra các số lẻ
    i = 3
    while i * i <= n:
        if n % i == 0:
            count = 0
            while n % i == 0:
                count += 1
                n //= i
            thua_so.append((i, count))
        i += 2
    
    # Nếu n > 1 thì n là số nguyên tố
    if n > 1:
        thua_so.append((n, 1))
    
    return thua_so


def hien_thi_phan_tich(n: int) -> str:
    """
    Hiển thị phân tích thừa số nguyên tố dưới dạng chuỗi
    
    Args:
        n: Số cần phân tích
    Returns:
        Chuỗi biểu diễn phân tích
    
    Ví dụ: "60 = 2^2 × 3 × 5"
    """
    if n < 2:
        return f"{n} không phân tích được"
    
    thua_so = phan_tich_thua_so_nguyen_to(n)
    parts = []
    
    for so, mu in thua_so:
        if mu == 1:
            parts.append(str(so))
        else:
            parts.append(f"{so}^{mu}")
    
    return f"{abs(n)} = " + " × ".join(parts)


# ============= CHIA HẾT =============

def chia_het_cho(a: int, b: int) -> bool:
    """
    Kiểm tra a có chia hết cho b không
    
    Args:
        a: Số bị chia
        b: Số chia
    Returns:
        True nếu a chia hết cho b
    """
    if b == 0:
        return False
    return a % b == 0


def chia_het_cho_2(n: int) -> bool:
    """Kiểm tra n có chia hết cho 2 không"""
    return n % 2 == 0


def chia_het_cho_3(n: int) -> bool:
    """Kiểm tra n có chia hết cho 3 không (tổng các chữ số chia hết cho 3)"""
    return sum(int(digit) for digit in str(abs(n))) % 3 == 0


def chia_het_cho_5(n: int) -> bool:
    """Kiểm tra n có chia hết cho 5 không"""
    return n % 5 == 0


def chia_het_cho_9(n: int) -> bool:
    """Kiểm tra n có chia hết cho 9 không (tổng các chữ số chia hết cho 9)"""
    return sum(int(digit) for digit in str(abs(n))) % 9 == 0


# ============= LUỸ THỪA =============

def luy_thua(co_so: Union[int, float], so_mu: int) -> Union[int, float]:
    """
    Tính lũy thừa: co_so^so_mu
    
    Args:
        co_so: Cơ số
        so_mu: Số mũ
    Returns:
        Kết quả của phép tính lũy thừa
    """
    return co_so ** so_mu


def luy_thua_nhanh(co_so: int, so_mu: int, mod: int = None) -> int:
    """
    Tính lũy thừa nhanh (phương pháp bình phương có lặp)
    
    Args:
        co_so: Cơ số
        so_mu: Số mũ
        mod: Số dư (nếu có)
    Returns:
        co_so^so_mu (mod mod nếu mod được chỉ định)
    """
    if mod:
        return pow(co_so, so_mu, mod)
    return pow(co_so, so_mu)


def can_bac_n(so: float, bac: int) -> float:
    """
    Tính căn bậc n của số
    
    Args:
        so: Số cần tính căn
        bac: Bậc của căn
    Returns:
        Căn bậc n của số
    """
    if bac == 0:
        raise ValueError("Bậc căn phải khác 0")
    return so ** (1 / bac)


# ============= GIẢI PHƯƠNG TRÌNH =============

def giai_phuong_trinh_bac_nhat(a: float, b: float) -> Union[float, str]:
    """
    Giải phương trình bậc nhất: ax + b = 0
    
    Args:
        a: Hệ số a
        b: Hệ số b
    Returns:
        Nghiệm hoặc thông báo
    """
    if a == 0:
        if b == 0:
            return "Phương trình vô số nghiệm"
        else:
            return "Phương trình vô nghiệm"
    return -b / a


def giai_phuong_trinh_bac_hai(a: float, b: float, c: float) -> Union[Tuple[float, float], str]:
    """
    Giải phương trình bậc hai: ax² + bx + c = 0
    
    Args:
        a, b, c: Các hệ số
    Returns:
        Nghiệm hoặc thông báo
    """
    if a == 0:
        result = giai_phuong_trinh_bac_nhat(b, c)
        if isinstance(result, str):
            return result
        return f"Phương trình bậc nhất có nghiệm x = {result}"
    
    delta = b**2 - 4*a*c
    
    if delta < 0:
        return "Phương trình vô nghiệm (Delta < 0)"
    elif delta == 0:
        x = -b / (2*a)
        return f"Phương trình có nghiệm kép x = {x}"
    else:
        x1 = (-b + math.sqrt(delta)) / (2*a)
        x2 = (-b - math.sqrt(delta)) / (2*a)
        return (x1, x2)


# ============= GIẢI BẤT PHƯƠNG TRÌNH =============

def giai_bat_phuong_trinh_bac_nhat(a: float, b: float, dau: str) -> str:
    """
    Giải bất phương trình bậc nhất: ax + b [dấu] 0
    
    Args:
        a: Hệ số a
        b: Hệ số b
        dau: Dấu bất phương trình ('>', '<', '>=', '<=')
    Returns:
        Miền nghiệm
    """
    if a == 0:
        if dau in ['>', '>=']:
            return "Vô nghiệm" if b >= 0 else "Mọi x ∈ ℝ"
        else:
            return "Mọi x ∈ ℝ" if b < 0 else "Vô nghiệm"
    
    x0 = -b / a
    
    if a > 0:
        if dau == '>':
            return f"x > {x0}"
        elif dau == '>=':
            return f"x >= {x0}"
        elif dau == '<':
            return f"x < {x0}"
        else:  # '<='
            return f"x <= {x0}"
    else:  # a < 0
        if dau == '>':
            return f"x < {x0}"
        elif dau == '>=':
            return f"x <= {x0}"
        elif dau == '<':
            return f"x > {x0}"
        else:  # '<='
            return f"x >= {x0}"


# ============= HỆ PHƯƠNG TRÌNH =============

def giai_he_phuong_trinh_2_an(a1: float, b1: float, c1: float,
                                a2: float, b2: float, c2: float) -> Union[Tuple[float, float], str]:
    """
    Giải hệ phương trình 2 ẩn:
    a1*x + b1*y = c1
    a2*x + b2*y = c2
    
    Args:
        a1, b1, c1: Hệ số phương trình 1
        a2, b2, c2: Hệ số phương trình 2
    Returns:
        (x, y) hoặc thông báo
    """
    D = a1*b2 - a2*b1
    Dx = c1*b2 - c2*b1
    Dy = a1*c2 - a2*c1
    
    if D != 0:
        x = Dx / D
        y = Dy / D
        return (x, y)
    else:
        if Dx == 0 and Dy == 0:
            return "Hệ phương trình vô số nghiệm"
        else:
            return "Hệ phương trình vô nghiệm"


# ============= HÀM TIỆN ÍCH =============

def la_so_hoan_hao(n: int) -> bool:
    """
    Kiểm tra n có phải số hoàn hảo không
    (Số hoàn hảo = tổng các ước thực sự)
    
    Ví dụ: 6 = 1 + 2 + 3
    """
    if n < 2:
        return False
    uoc = tim_uoc_so(n)
    return sum(uoc[:-1]) == n  # Không tính n


def la_so_nguyen_to_cung_nhau(a: int, b: int) -> bool:
    """
    Kiểm tra a và b có nguyên tố cùng nhau không (UCLN = 1)
    """
    return ucln(a, b) == 1


def fibonacci(n: int) -> int:
    """
    Tính số Fibonacci thứ n
    F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)
    """
    if n <= 1:
        return n
    a, b = 0, 1
    for _ in range(2, n + 1):
        a, b = b, a + b
    return b


def giai_thua(n: int) -> int:
    """
    Tính giai thừa n! = 1 × 2 × 3 × ... × n
    """
    if n < 0:
        raise ValueError("Giai thừa không xác định cho số âm")
    if n == 0 or n == 1:
        return 1
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result


def to_hop(n: int, k: int) -> int:
    """
    Tính tổ hợp chập k của n: C(n, k) = n! / (k! × (n-k)!)
    """
    if k > n or k < 0:
        return 0
    if k == 0 or k == n:
        return 1
    
    # Tối ưu: C(n, k) = C(n, n-k)
    k = min(k, n - k)
    
    result = 1
    for i in range(k):
        result = result * (n - i) // (i + 1)
    return result


# ============= VÍ DỤ SỬ DỤNG =============

if __name__ == "__main__":
    print("=" * 60)
    print("THƯ VIỆN TOÁN HỌC PYTHON")
    print("=" * 60)
    
    # Số nguyên tố
    print("\n1. SỐ NGUYÊN TỐ:")
    print(f"17 là số nguyên tố: {la_so_nguyen_to(17)}")
    print(f"10 số nguyên tố đầu tiên: {n_so_nguyen_to_dau_tien(10)}")
    print(f"Số nguyên tố <= 30: {sang_nguyen_to(30)}")
    
    # Ước số
    print("\n2. ƯỚC SỐ:")
    print(f"Ước số của 24: {tim_uoc_so(24)}")
    print(f"Số lượng ước của 24: {dem_uoc_so(24)}")
    print(f"Tổng các ước của 24: {tong_uoc_so(24)}")
    
    # Bội số
    print("\n3. BỘI SỐ:")
    print(f"5 bội số đầu tiên của 7: {tim_boi_so(7, 5)}")
    print(f"35 có phải bội của 7: {co_phai_boi_so(35, 7)}")
    
    # UCLN và BCNN
    print("\n4. UCLN VÀ BCNN:")
    print(f"UCLN(48, 18) = {ucln(48, 18)}")
    print(f"BCNN(48, 18) = {bcnn(48, 18)}")
    print(f"UCLN(12, 18, 24) = {ucln_nhieu_so(12, 18, 24)}")
    print(f"BCNN(12, 18, 24) = {bcnn_nhieu_so(12, 18, 24)}")
    
    # Phân tích thừa số nguyên tố
    print("\n5. PHÂN TÍCH THỪA SỐ NGUYÊN TỐ:")
    print(hien_thi_phan_tich(60))
    print(hien_thi_phan_tich(100))
    print(f"Phân tích 360: {phan_tich_thua_so_nguyen_to(360)}")
    
    # Chia hết
    print("\n6. CHIA HẾT:")
    print(f"48 chia hết cho 6: {chia_het_cho(48, 6)}")
    print(f"123 chia hết cho 3: {chia_het_cho_3(123)}")
    print(f"125 chia hết cho 5: {chia_het_cho_5(125)}")
    
    # Lũy thừa
    print("\n7. LŨY THỪA:")
    print(f"2^10 = {luy_thua(2, 10)}")
    print(f"Căn bậc 3 của 27 = {can_bac_n(27, 3)}")
    print(f"2^100 mod 97 = {luy_thua_nhanh(2, 100, 97)}")
    
    # Phương trình
    print("\n8. GIẢI PHƯƠNG TRÌNH:")
    print(f"2x + 6 = 0 => x = {giai_phuong_trinh_bac_nhat(2, 6)}")
    print(f"x² - 5x + 6 = 0 => x = {giai_phuong_trinh_bac_hai(1, -5, 6)}")
    
    # Bất phương trình
    print("\n9. BẤT PHƯƠNG TRÌNH:")
    print(f"2x + 4 > 0 => {giai_bat_phuong_trinh_bac_nhat(2, 4, '>')}")
    print(f"-3x + 6 >= 0 => {giai_bat_phuong_trinh_bac_nhat(-3, 6, '>=')}")
    
    # Hệ phương trình
    print("\n10. HỆ PHƯƠNG TRÌNH:")
    print(f"x + y = 5, 2x - y = 1 => {giai_he_phuong_trinh_2_an(1, 1, 5, 2, -1, 1)}")
    
    # Các hàm tiện ích
    print("\n11. HÀM TIỆN ÍCH:")
    print(f"6 là số hoàn hảo: {la_so_hoan_hao(6)}")
    print(f"15 và 28 nguyên tố cùng nhau: {la_so_nguyen_to_cung_nhau(15, 28)}")
    print(f"Fibonacci thứ 10: {fibonacci(10)}")
    print(f"5! = {giai_thua(5)}")
    print(f"C(5, 2) = {to_hop(5, 2)}")
    
    print("\n" + "=" * 60)