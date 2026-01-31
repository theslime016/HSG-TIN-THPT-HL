from flask import Flask, render_template_string, request
import requests
from datetime import datetime

app = Flask(__name__)

WEATHER_CODES = {
    0: "Trời quang", 1: "Quang đãng", 2: "Mây rải rác", 3: "U ám",
    45: "Sương mù", 48: "Sương muối", 51: "Mưa phùn", 61: "Mưa nhẹ",
    71: "Tuyết rơi", 80: "Mưa rào", 95: "Dông"
}

def get_location_name(lat, lon):
    try:
        url = f"https://nominatim.openstreetmap.org/reverse?format=json&lat={lat}&lon={lon}"
        headers = {'User-Agent': 'EnvAnalyzer/1.0'}
        res = requests.get(url, headers=headers).json()
        address = res.get('address', {})
        return address.get('city') or address.get('town') or address.get('suburb') or "Vị trí xác định"
    except:
        return "Vị trí hiện tại"

def get_environmental_data(lat, lon):
    air_url = f"https://air-quality-api.open-meteo.com/v1/air-quality?latitude={lat}&longitude={lon}&current=us_aqi,pm10,pm2_5,nitrogen_dioxide"
    weather_url = f"https://api.open-meteo.com/v1/forecast?latitude={lat}&longitude={lon}&current=temperature_2m,relative_humidity_2m,windspeed_10m,weathercode&daily=weathercode,temperature_2m_max,temperature_2m_min&timezone=auto"
    
    try:
        air_res = requests.get(air_url).json()
        weather_res = requests.get(weather_url).json()
        aqi = air_res["current"]["us_aqi"]
        
        forecast = []
        for i in range(1, 4):
            forecast.append({
                "date": weather_res["daily"]["time"][i],
                "max": weather_res["daily"]["temperature_2m_max"][i],
                "min": weather_res["daily"]["temperature_2m_min"][i],
                "desc": WEATHER_CODES.get(weather_res["daily"]["weathercode"][i], "Nắng nhẹ")
            })

        return {
            "aqi": aqi,
            "status": evaluate_aqi(aqi),
            "location_name": get_location_name(lat, lon),
            "pm25": air_res["current"]["pm2_5"],
            "temp": weather_res["current"]["temperature_2m"],
            "humidity": weather_res["current"]["relative_humidity_2m"],
            "desc": WEATHER_CODES.get(weather_res["current"]["weathercode"], "Không xác định"),
            "forecast": forecast,
            "lat": lat, "lon": lon
        }
    except: return None

def evaluate_aqi(aqi):
    if aqi <= 50: return ("Tốt", "text-green-500", "bg-green-50")
    elif aqi <= 100: return ("Trung bình", "text-yellow-600", "bg-yellow-50")
    elif aqi <= 150: return ("Kém", "text-orange-500", "bg-orange-50")
    else: return ("Xấu", "text-red-600", "bg-red-50")

HTML_TEMPLATE = """
<!DOCTYPE html>
<html lang="vi">
<head>
    <meta charset="UTF-8">
    <title>Giám sát Môi trường Toàn diện</title>
    <script src="https://cdn.tailwindcss.com"></script>
    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css" />
    <script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"></script>
</head>
<body class="bg-slate-100 p-4 font-sans text-slate-900">
    <div class="max-w-7xl mx-auto space-y-6">
        <!-- Search & Map Section -->
        <div class="bg-white p-4 rounded-3xl shadow-lg border relative overflow-hidden">
            <div id="map" class="w-full h-[500px] rounded-2xl bg-slate-200"></div>
            
            <div class="absolute top-8 left-8 z-[1000] space-y-3 w-full max-w-sm">
                <!-- Search Bar -->
                <div class="flex shadow-2xl rounded-2xl overflow-hidden border-2 border-white">
                    <input type="text" id="search-input" placeholder="Tìm thành phố, địa điểm..." 
                           class="flex-1 p-3 outline-none text-sm" onkeypress="if(event.key==='Enter') searchLocation()">
                    <button onclick="searchLocation()" class="bg-blue-600 text-white px-5 hover:bg-blue-700 transition">
                        🔍
                    </button>
                </div>
                
                <!-- Info Card -->
                <div class="bg-white/95 backdrop-blur p-5 rounded-2xl shadow-xl border border-white">
                    <h1 class="text-xl font-bold text-slate-800">{{ data.location_name }}</h1>
                    <p class="text-slate-500 text-xs mb-4">Tọa độ: {{ data.lat }}, {{ data.lon }}</p>
                    <div class="flex gap-2">
                        <button onclick="getLocation()" class="flex-1 bg-slate-800 text-white py-2 rounded-xl text-xs font-bold hover:bg-slate-900 transition">📍 Vị trí hiện tại</button>
                    </div>
                </div>
            </div>
        </div>

        <div class="grid grid-cols-1 lg:grid-cols-12 gap-6">
            <div class="lg:col-span-8 grid grid-cols-1 md:grid-cols-2 gap-6">
                <div class="{{ data.status[2] }} p-8 rounded-3xl border flex items-center justify-between shadow-sm">
                    <div>
                        <p class="font-bold uppercase text-[10px] opacity-60">Chỉ số AQI</p>
                        <h2 class="text-5xl font-black {{ data.status[1] }}">{{ data.aqi }}</h2>
                        <p class="font-bold text-lg mt-1 text-slate-700">{{ data.status[0] }}</p>
                    </div>
                    <div class="text-right">
                        <p class="text-[10px] font-bold text-gray-400">PM2.5</p>
                        <p class="text-3xl font-bold text-slate-800">{{ data.pm25 }}</p>
                    </div>
                </div>

                <div class="bg-white p-8 rounded-3xl border shadow-sm flex items-center justify-between">
                    <div>
                        <p class="font-bold uppercase text-[10px] text-gray-400">Thời tiết</p>
                        <h2 class="text-5xl font-black text-slate-800">{{ data.temp }}°C</h2>
                        <p class="font-bold text-lg mt-1 text-slate-700">{{ data.desc }}</p>
                    </div>
                    <div class="text-right">
                        <p class="text-[10px] font-bold text-gray-400">Độ ẩm</p>
                        <p class="text-3xl font-bold text-slate-800">{{ data.humidity }}%</p>
                    </div>
                </div>

                <div class="md:col-span-2 bg-slate-800 text-white p-6 rounded-3xl shadow-lg relative overflow-hidden">
                    <div class="relative z-10">
                        <h3 class="font-bold mb-2">Đánh giá chung</h3>
                        <p class="text-sm opacity-80 leading-relaxed">
                            Khu vực <strong>{{ data.location_name }}</strong> đang có chất lượng không khí <strong>{{ data.status[0].lower() }}</strong>. 
                            {% if data.aqi > 100 %} Nên đeo khẩu trang khi ra ngoài để bảo vệ hô hấp. {% else %} Điều kiện rất lý tưởng cho các hoạt động ngoài trời. {% endif %}
                        </p>
                    </div>
                    <div class="absolute -right-4 -bottom-4 opacity-10 text-8xl">🌍</div>
                </div>
            </div>

            <div class="lg:col-span-4 bg-white p-6 rounded-3xl shadow-sm border">
                <h2 class="font-bold mb-4 flex justify-between items-center text-slate-800">
                    Dự báo 3 ngày <span class="text-[10px] bg-blue-100 text-blue-600 px-2 py-1 rounded-full uppercase">Tiếp theo</span>
                </h2>
                <div class="space-y-4">
                    {% for day in data.forecast %}
                    <div class="flex justify-between items-center p-3 bg-slate-50 rounded-xl hover:bg-slate-100 transition">
                        <span class="text-xs font-bold text-slate-400 w-16">{{ day.date[5:] }}</span>
                        <span class="text-sm font-semibold flex-1">{{ day.desc }}</span>
                        <div class="text-right min-w-[60px]">
                            <span class="text-red-500 font-bold mr-1">{{ day.max }}°</span>
                            <span class="text-blue-500 font-bold">{{ day.min }}°</span>
                        </div>
                    </div>
                    {% endfor %}
                </div>
            </div>
        </div>
    </div>

    <script>
        document.addEventListener('DOMContentLoaded', function() {
            const params = new URLSearchParams(window.location.search);
            // Nếu không có tọa độ trên URL, tự động yêu cầu vị trí GPS
            if (!params.has('lat') || !params.has('lon')) {
                getLocation();
            }

            const lat = {{ data.lat }};
            const lon = {{ data.lon }};
            const map = L.map('map').setView([lat, lon], 14);
            
            L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
                attribution: '&copy; OpenStreetMap'
            }).addTo(map);

            L.marker([lat, lon]).addTo(map).bindPopup('{{ data.location_name }}').openPopup();
        });

        function getLocation() {
            if (navigator.geolocation) {
                navigator.geolocation.getCurrentPosition((pos) => {
                    window.location.href = `/?lat=${pos.coords.latitude}&lon=${pos.coords.longitude}`;
                }, (err) => {
                    console.log("GPS bị chặn hoặc lỗi.");
                });
            }
        }

        async function searchLocation() {
            const query = document.getElementById('search-input').value;
            if (!query) return;
            
            try {
                const response = await fetch(`https://nominatim.openstreetmap.org/search?format=json&q=${encodeURIComponent(query)}`);
                const data = await response.json();
                if (data.length > 0) {
                    const { lat, lon } = data[0];
                    window.location.href = `/?lat=${lat}&lon=${lon}`;
                } else {
                    alert("Không tìm thấy địa điểm này!");
                }
            } catch (error) {
                alert("Lỗi khi tìm kiếm địa điểm.");
            }
        }
    </script>
</body>
</html>
"""

@app.route('/')
def index():
    # Tọa độ mặc định (Hà Nội) nếu chưa có tham số
    lat = request.args.get('lat', default=21.0285, type=float)
    lon = request.args.get('lon', default=105.8542, type=float)
    env_data = get_environmental_data(lat, lon)
    return render_template_string(HTML_TEMPLATE, data=env_data)

if __name__ == '__main__':
    app.run(debug=True, port=5000)