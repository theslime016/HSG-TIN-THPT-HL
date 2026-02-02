-- Script Auto Farm Premium cho Việt Dũng đẹp zai
-- Đã sửa lỗi: Unicode U+a0 và TextXAlignment
-- Updated: Height = 15, Farm ALL mobs, Click Delay 0.5s

local UserInputService = game:GetService("UserInputService")
local RunService = game:GetService("RunService")
local ReplicatedStorage = game:GetService("ReplicatedStorage")
local TweenService = game:GetService("TweenService")
local VirtualInputManager = game:GetService("VirtualInputManager")
local Players = game:GetService("Players")
local Workspace = game:GetService("Workspace")
local CoreGui = game:GetService("CoreGui")

local LocalPlayer = Players.LocalPlayer

-- === CẤU HÌNH MẶC ĐỊNH ===
local Config = {
    -- TargetName không còn cần thiết vì đã chuyển sang farm tất cả
    ScanFolder = Workspace:WaitForChild("NPCs"):WaitForChild("Custom"), -- Thư mục chứa NPC
    
    -- Remote Events
    MeleeEvent = ReplicatedStorage:WaitForChild("MeleeStorage").Events.Hit,
    
    -- Trạng thái
    IsFarming = false, 
    
    -- Thông số
    TeleportHeight = 15,  -- Khoảng cách trên đầu quái (Y) [Đã chỉnh lên 15]
    TweenSpeed = 50,      -- Tốc độ bay mặc định
    ClickDelay = 0.5      -- Tốc độ đánh liên tục [Đã chỉnh xuống 0.5]
}

-- === HỆ THỐNG UI (MODERN DESIGN) ===

-- Xóa UI cũ nếu tồn tại
if CoreGui:FindFirstChild("VietDung_Hub_V2") then
    CoreGui.VietDung_Hub_V2:Destroy()
end

local ScreenGui = Instance.new("ScreenGui")
ScreenGui.Name = "VietDung_Hub_V2"
ScreenGui.Parent = CoreGui
ScreenGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling

-- 1. Main Frame
local MainFrame = Instance.new("Frame")
MainFrame.Name = "MainFrame"
MainFrame.Parent = ScreenGui
MainFrame.BackgroundColor3 = Color3.fromRGB(25, 25, 35)
MainFrame.BorderSizePixel = 0
MainFrame.Position = UDim2.new(0, 30, 0.6, 0)
MainFrame.Size = UDim2.new(0, 260, 0, 280)
MainFrame.ClipsDescendants = true

local UICorner = Instance.new("UICorner")
UICorner.CornerRadius = UDim.new(0, 12)
UICorner.Parent = MainFrame

local UIStroke = Instance.new("UIStroke")
UIStroke.Parent = MainFrame
UIStroke.Color = Color3.fromRGB(60, 60, 80)
UIStroke.Thickness = 1.5

-- 2. Header
local Header = Instance.new("Frame")
Header.Name = "Header"
Header.Parent = MainFrame
Header.BackgroundColor3 = Color3.fromRGB(35, 35, 45)
Header.Size = UDim2.new(1, 0, 0, 40)
Header.BorderSizePixel = 0

local HeaderCorner = Instance.new("UICorner")
HeaderCorner.CornerRadius = UDim.new(0, 12)
HeaderCorner.Parent = Header

local FixPatch = Instance.new("Frame")
FixPatch.Parent = Header
FixPatch.BackgroundColor3 = Color3.fromRGB(35, 35, 45)
FixPatch.BorderSizePixel = 0
FixPatch.Size = UDim2.new(1, 0, 0, 10)
FixPatch.Position = UDim2.new(0, 0, 1, -10)

local Title = Instance.new("TextLabel")
Title.Parent = Header
Title.BackgroundTransparency = 1
Title.Position = UDim2.new(0, 15, 0, 0)
Title.Size = UDim2.new(1, -30, 1, 0)
Title.Font = Enum.Font.GothamBold
Title.Text = "VIỆT DŨNG HUB 👑"
Title.TextColor3 = Color3.fromRGB(255, 215, 0)
Title.TextSize = 16
Title.TextXAlignment = Enum.TextXAlignment.Left

-- 3. Content Container
local Content = Instance.new("Frame")
Content.Name = "Content"
Content.Parent = MainFrame
Content.BackgroundTransparency = 1
Content.Position = UDim2.new(0, 15, 0, 50)
Content.Size = UDim2.new(1, -30, 1, -60)

local UIListLayout = Instance.new("UIListLayout")
UIListLayout.Parent = Content
UIListLayout.SortOrder = Enum.SortOrder.LayoutOrder
UIListLayout.Padding = UDim.new(0, 10)

-- --- A. Nút Trạng Thái (Status) ---
local StatusFrame = Instance.new("Frame")
StatusFrame.BackgroundTransparency = 1
StatusFrame.Size = UDim2.new(1, 0, 0, 30)
StatusFrame.LayoutOrder = 1
StatusFrame.Parent = Content

local StatusLabel = Instance.new("TextLabel")
StatusLabel.Parent = StatusFrame
StatusLabel.BackgroundTransparency = 1
StatusLabel.Size = UDim2.new(1, 0, 1, 0)
StatusLabel.Font = Enum.Font.GothamBold
StatusLabel.Text = "STATUS: OFF 🔴"
StatusLabel.TextColor3 = Color3.fromRGB(255, 80, 80)
StatusLabel.TextSize = 18
StatusLabel.TextXAlignment = Enum.TextXAlignment.Left

-- --- B. Bộ Đếm Quái ---
local CounterFrame = Instance.new("Frame")
CounterFrame.BackgroundColor3 = Color3.fromRGB(45, 45, 55)
CounterFrame.Size = UDim2.new(1, 0, 0, 35)
CounterFrame.LayoutOrder = 2
CounterFrame.Parent = Content

local CounterCorner = Instance.new("UICorner")
CounterCorner.CornerRadius = UDim.new(0, 8)
CounterCorner.Parent = CounterFrame

local CounterLabel = Instance.new("TextLabel")
CounterLabel.Parent = CounterFrame
CounterLabel.BackgroundTransparency = 1
CounterLabel.Size = UDim2.new(1, 0, 1, 0)
CounterLabel.Font = Enum.Font.GothamMedium
CounterLabel.Text = "Enemy Count: 0"
CounterLabel.TextColor3 = Color3.fromRGB(200, 200, 255)
CounterLabel.TextSize = 14

-- --- C. Chỉnh Tốc Độ ---
local SpeedFrame = Instance.new("Frame")
SpeedFrame.BackgroundTransparency = 1
SpeedFrame.Size = UDim2.new(1, 0, 0, 50)
SpeedFrame.LayoutOrder = 3
SpeedFrame.Parent = Content

local SpeedTitle = Instance.new("TextLabel")
SpeedTitle.Parent = SpeedFrame
SpeedTitle.BackgroundTransparency = 1
SpeedTitle.Size = UDim2.new(1, 0, 0, 20)
SpeedTitle.Font = Enum.Font.Gotham
SpeedTitle.Text = "Tween Speed:"
SpeedTitle.TextColor3 = Color3.fromRGB(180, 180, 180)
SpeedTitle.TextSize = 13
SpeedTitle.TextXAlignment = Enum.TextXAlignment.Left

local SpeedInput = Instance.new("TextBox")
SpeedInput.Parent = SpeedFrame
SpeedInput.BackgroundColor3 = Color3.fromRGB(45, 45, 55)
SpeedInput.Position = UDim2.new(0, 0, 0, 22)
SpeedInput.Size = UDim2.new(1, 0, 0, 28)
SpeedInput.Font = Enum.Font.GothamBold
SpeedInput.Text = tostring(Config.TweenSpeed)
SpeedInput.TextColor3 = Color3.fromRGB(255, 255, 255)
SpeedInput.TextSize = 14
SpeedInput.PlaceholderText = "Nhập tốc độ..."

local SpeedCorner = Instance.new("UICorner")
SpeedCorner.CornerRadius = UDim.new(0, 6)
SpeedCorner.Parent = SpeedInput

SpeedInput.FocusLost:Connect(function(enterPressed)
    local num = tonumber(SpeedInput.Text)
    if num then
        Config.TweenSpeed = num
        SpeedInput.Text = tostring(num)
    else
        SpeedInput.Text = tostring(Config.TweenSpeed)
    end
end)

-- --- D. Hướng dẫn ---
local NoteLabel = Instance.new("TextLabel")
NoteLabel.Parent = Content
NoteLabel.LayoutOrder = 4
NoteLabel.BackgroundTransparency = 1
NoteLabel.Size = UDim2.new(1, 0, 0, 40)
NoteLabel.Font = Enum.Font.Gotham
NoteLabel.Text = "Bấm [F] để Bật/Tắt\nFarm TẤT CẢ quái trong map"
NoteLabel.TextColor3 = Color3.fromRGB(150, 150, 150)
NoteLabel.TextSize = 12
NoteLabel.TextWrapped = true

-- === LOGIC SCRIPT ===

local function UpdateStatusUI()
    if Config.IsFarming then
        StatusLabel.Text = "STATUS: FARMING 🟢"
        StatusLabel.TextColor3 = Color3.fromRGB(80, 255, 80)
        UIStroke.Color = Color3.fromRGB(80, 255, 80)
    else
        StatusLabel.Text = "STATUS: OFF 🔴"
        StatusLabel.TextColor3 = Color3.fromRGB(255, 80, 80)
        UIStroke.Color = Color3.fromRGB(60, 60, 80)
    end
end

-- Cập nhật đếm quái: Tính tất cả quái có Humanoid
local function UpdateEnemyCount()
    local count = 0
    pcall(function()
        for _, v in pairs(Config.ScanFolder:GetChildren()) do
            -- Bỏ check tên, chỉ check có phải là quái sống không
            if v:FindFirstChild("Humanoid") and v.Humanoid.Health > 0 and v:FindFirstChild("HumanoidRootPart") then
                count = count + 1
            end
        end
    end)
    CounterLabel.Text = "Enemy Found: " .. count .. " 💀"
end

task.spawn(function()
    while true do
        UpdateEnemyCount()
        task.wait(1)
    end
end)

-- Tìm quái gần nhất: Không lọc tên, lấy tất cả
local function GetClosestTarget()
    local closestDist = math.huge
    local closestTarget = nil
    local char = LocalPlayer.Character
    if not char or not char:FindFirstChild("HumanoidRootPart") then return nil end
    local myPos = char.HumanoidRootPart.Position

    pcall(function()
        for _, v in pairs(Config.ScanFolder:GetChildren()) do
            -- Bỏ check tên
            if v:FindFirstChild("Humanoid") and v.Humanoid.Health > 0 and v:FindFirstChild("HumanoidRootPart") then
                local dist = (v.HumanoidRootPart.Position - myPos).Magnitude
                if dist < closestDist then
                    closestDist = dist
                    closestTarget = v
                end
            end
        end
    end)
    return closestTarget
end

local function SetAntiGravity(enabled)
    local char = LocalPlayer.Character
    if not char or not char:FindFirstChild("HumanoidRootPart") then return end
    local hrp = char.HumanoidRootPart
    
    local bv = hrp:FindFirstChild("FarmAntiGravity")
    
    if enabled then
        if not bv then
            bv = Instance.new("BodyVelocity")
            bv.Name = "FarmAntiGravity"
            bv.MaxForce = Vector3.new(math.huge, math.huge, math.huge)
            bv.Velocity = Vector3.new(0, 0, 0)
            bv.Parent = hrp
        end
    else
        if bv then
            bv:Destroy()
        end
    end
end

UserInputService.InputBegan:Connect(function(input, gameProcessed)
    if not gameProcessed and input.KeyCode == Enum.KeyCode.F then
        Config.IsFarming = not Config.IsFarming
        UpdateStatusUI()
        
        if not Config.IsFarming then
            SetAntiGravity(false)
            
            -- Tắt NoClip khi dừng farm
            local char = LocalPlayer.Character
            if char then
                for _, part in pairs(char:GetChildren()) do
                    if part:IsA("BasePart") then
                        part.CanCollide = true
                    end
                end
            end
        end
    end
end)

-- NO CLIP LOOP
RunService.Stepped:Connect(function()
    if Config.IsFarming then
        local char = LocalPlayer.Character
        if char then
            for _, part in pairs(char:GetChildren()) do
                if part:IsA("BasePart") then
                    part.CanCollide = false
                end
            end
        end
    end
end)

-- Main Loop: Tween + Auto Farm
task.spawn(function()
    while true do
        task.wait()
        
        if Config.IsFarming then
            local target = GetClosestTarget()
            local char = LocalPlayer.Character
            
            if target and char and char:FindFirstChild("HumanoidRootPart") then
                local hrp = char.HumanoidRootPart
                local targetHRP = target.HumanoidRootPart
                
                -- Vị trí trên đầu (Cao 15 stud)
                local destination = targetHRP.CFrame * CFrame.new(0, Config.TeleportHeight, 0)
                
                SetAntiGravity(true)
                
                local distance = (hrp.Position - destination.Position).Magnitude
                
                if distance > 2 then
                    local tweenTime = distance / Config.TweenSpeed
                    local tweenInfo = TweenInfo.new(tweenTime, Enum.EasingStyle.Linear)
                    local tween = TweenService:Create(hrp, tweenInfo, {CFrame = destination})
                    tween:Play()
                else
                    hrp.CFrame = destination
                end
                
                -- Attack Remote (Gửi liên tục khi tiếp cận)
                pcall(function()
                    local args = {
                        [1] = targetHRP,
                        [2] = targetHRP.Position
                    }
                    Config.MeleeEvent:FireServer(unpack(args))
                end)
            else
                SetAntiGravity(false)
            end
        end
    end
end)

-- Auto Click Loop: Đánh liên tục 0.5s đến khi quái chết
task.spawn(function()
    while true do
        if Config.IsFarming then
            local target = GetClosestTarget()
            if target then
                -- Nếu có mục tiêu -> Click liên tục
                VirtualInputManager:SendMouseButtonEvent(0, 0, 0, true, game, 1)
                task.wait(0.05)
                VirtualInputManager:SendMouseButtonEvent(0, 0, 0, false, game, 1)
                
                -- Delay 0.5s rồi lặp lại ngay nếu quái chưa chết (vòng lặp tiếp theo sẽ check lại target)
                task.wait(Config.ClickDelay)
            else
                -- Không có mục tiêu thì đợi 1s tìm tiếp
                task.wait(1)
            end
        else
            task.wait(1)
        end
    end
end)

-- === ESP SYSTEM ===
local function AddESP(model)
    if not model or not model:IsA("Model") then return end
    if model:FindFirstChild("HighlightESP") then return end
    -- Bỏ check tên, apply cho tất cả Model có Humanoid
    if not model:FindFirstChild("Humanoid") then return end

    local highlight = Instance.new("Highlight")
    highlight.Name = "HighlightESP"
    highlight.Adornee = model
    highlight.FillColor = Color3.fromRGB(255, 50, 50)
    highlight.OutlineColor = Color3.fromRGB(255, 255, 255)
    highlight.FillTransparency = 0.5
    highlight.Parent = model

    if model:WaitForChild("Head", 5) then
        local bg = Instance.new("BillboardGui")
        bg.Name = "InfoESP"
        bg.Adornee = model.Head
        bg.Size = UDim2.new(0, 100, 0, 50)
        bg.StudsOffset = Vector3.new(0, 2, 0)
        bg.AlwaysOnTop = true
        bg.Parent = model.Head

        local textLab = Instance.new("TextLabel")
        textLab.Parent = bg
        textLab.Size = UDim2.new(1, 0, 1, 0)
        textLab.BackgroundTransparency = 1
        textLab.TextColor3 = Color3.fromRGB(255, 255, 0)
        textLab.TextStrokeTransparency = 0
        textLab.Font = Enum.Font.GothamBold
        textLab.TextSize = 12
        textLab.Text = model.Name
        
        task.spawn(function()
            while model and model.Parent and model:FindFirstChild("Humanoid") do
                local hum = model.Humanoid
                textLab.Text = "HP: " .. math.floor(hum.Health)
                task.wait(0.5)
            end
            if bg then bg:Destroy() end
        end)
    end
end

-- Scan Initial & Added
for _, v in pairs(Config.ScanFolder:GetChildren()) do AddESP(v) end
Config.ScanFolder.ChildAdded:Connect(function(child) 
    task.wait(0.5) 
    AddESP(child)
    UpdateEnemyCount()
end)
Config.ScanFolder.ChildRemoved:Connect(function()
    UpdateEnemyCount()
end)

print("Viet Dung Hub V2 Loaded Successfully!")