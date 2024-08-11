import datetime

class Vehicle:
    def __init__(self, ma_xe, so_xe, loai_xe, chu_xe, don_gia):
        self.ma_xe = ma_xe
        self.so_xe = so_xe
        self.loai_xe = loai_xe
        self.chu_xe = chu_xe
        self.don_gia = don_gia
        self.ngay_gui = datetime.datetime.now()

    def __str__(self):
        return f"Ma xe: {self.ma_xe}, So xe: {self.so_xe}, Loai xe: {self.loai_xe}, Chu xe: {self.chu_xe}, Don gia: {self.don_gia}, Ngay gui: {self.ngay_gui}"

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class Stack:
    def __init__(self):
        self.top = None

    def is_empty(self):
        return self.top is None

    def push(self, vehicle):
        new_node = Node(vehicle)
        new_node.next = self.top
        self.top = new_node
        print(f"Xe {vehicle.so_xe} đã vào bãi.")

    def pop(self):
        if self.is_empty():
            print("Bãi xe rỗng, không có xe nào để ra.")
            return None
        removed_data = self.top.data
        self.top = self.top.next
        print(f"Xe {removed_data.so_xe} đã ra khỏi bãi.")
        return removed_data

    def peek(self):
        if self.is_empty():
            print("Bãi xe rỗng.")
            return None
        return self.top.data

    def display(self):
        if self.is_empty():
            print("Bãi xe rỗng.")
            return
        current = self.top
        print("Các xe trong bãi hiện tại:")
        while current:
            print(current.data)
            current = current.next

    def find_most_common_vehicle_type(self):
        if self.is_empty():
            print("Bãi xe rỗng.")
            return None
        type_count = {}
        current = self.top
        while current:
            loai_xe = current.data.loai_xe
            if loai_xe in type_count:
                type_count[loai_xe] += 1
            else:
                type_count[loai_xe] = 1
            current = current.next
        most_common_type = max(type_count, key=type_count.get)
        print(f"Loại xe có nhiều nhất: {most_common_type} với {type_count[most_common_type]} xe.")
        return most_common_type

    def find_vehicle_by_type(self, loai_xe):
        if self.is_empty():
            print("Bãi xe rỗng.")
            return []
        current = self.top
        vehicles = []
        while current:
            if current.data.loai_xe == loai_xe:
                vehicles.append(current.data)
            current = current.next
        if vehicles:
            print(f"Đã tìm thấy {len(vehicles)} xe loại {loai_xe}:")
            for vehicle in vehicles:
                print(vehicle)
        else:
            print(f"Không tìm thấy xe loại {loai_xe}.")
        return vehicles

    def statistics_by_don_gia(self):
        if self.is_empty():
            print("Bãi xe rỗng.")
            return {}
        statistics = {}
        current = self.top
        while current:
            don_gia = current.data.don_gia
            if don_gia in statistics:
                statistics[don_gia] += 1
            else:
                statistics[don_gia] = 1
            current = current.next
        print("Thống kê xe theo đơn giá gởi:")
        for don_gia, count in statistics.items():
            print(f"Đơn giá: {don_gia}, Số lượng xe: {count}")
        return statistics

    def count_by_vehicle_type(self):
        if self.is_empty():
            print("Bãi xe rỗng.")
            return {}
        count = {}
        current = self.top
        while current:
            loai_xe = current.data.loai_xe
            if loai_xe in count:
                count[loai_xe] += 1
            else:
                count[loai_xe] = 1
            current = current.next
        print("Số lượng xe theo từng loại:")
        for loai_xe, so_luong in count.items():
            print(f"Loại xe: {loai_xe}, Số lượng: {so_luong}")
        return count

    def remove_vehicle(self, so_xe):
        if self.is_empty():
            print("Bãi xe rỗng.")
            return None
        current = self.top
        previous = None
        while current and current.data.so_xe != so_xe:
            previous = current
            current = current.next
        if current is None:
            print(f"Không tìm thấy xe có số {so_xe}.")
            return None
        if previous is None:
            self.top = current.next
        else:
            previous.next = current.next
        print(f"Xe {so_xe} đã ra khỏi bãi.")
        return current.data

    def count_vehicles(self):
        count = 0
        current = self.top
        while current:
            count += 1
            current = current.next
        print(f"Tổng số xe trong bãi: {count}")
        return count

    def calculate_revenue(self, start_date, end_date):
        if self.is_empty():
            print("Bãi xe rỗng.")
            return 0
        total_revenue = 0
        current = self.top
        while current:
            ngay_gui = current.data.ngay_gui
            if start_date <= ngay_gui <= end_date:
                total_revenue += current.data.don_gia
            current = current.next
        print(f"Doanh thu từ {start_date} đến {end_date}: {total_revenue}")
        return total_revenue

    def read_from_file(self, filename):
        try:
            with open(filename, 'r') as file:
                lines = file.readlines()
                for line in lines:
                    ma_xe, so_xe, loai_xe, chu_xe, don_gia = line.strip().split(',')
                    vehicle = Vehicle(ma_xe, so_xe, loai_xe, chu_xe, float(don_gia))
                    self.push(vehicle)
            print(f"Đọc dữ liệu từ file {filename} thành công.")
        except FileNotFoundError:
            print(f"File {filename} không tồn tại.")

    def write_to_file(self, filename):
        with open(filename, 'w') as file:
            current = self.top
            while current:
                vehicle = current.data
                line = f"{vehicle.ma_xe},{vehicle.so_xe},{vehicle.loai_xe},{vehicle.chu_xe},{vehicle.don_gia}\n"
                file.write(line)
                current = current.next
        print(f"Ghi dữ liệu ra file {filename} thành công.")


# Khởi tạo bãi xe
bai_xe = Stack()

# Ví dụ sử dụng:

# 1. Nhập xe từ bàn phím
ma_xe = "001"
so_xe = "79A-12345"
loai_xe = "Oto"
chu_xe = "Nguyen Van A"
don_gia = 50000
vehicle = Vehicle(ma_xe, so_xe, loai_xe, chu_xe, don_gia)
bai_xe.push(vehicle)

# 2. Đọc xe từ file
bai_xe.read_from_file('xe_data.txt')

# 3. Hiển thị tất cả các thông tin xe
bai_xe.display()

# 4. Thêm 1 xe mới vào stack
ma_xe_moi = "002"
so_xe_moi = "79B-54321"
loai_xe_moi = "Xe may"
chu_xe_moi = "Le Thi B"
don_gia_moi = 20000
xe_moi = Vehicle(ma_xe_moi, so_xe_moi, loai_xe_moi, chu_xe_moi, don_gia_moi)
bai_xe.push(xe_moi)

# 5. Tìm loại xe nào có nhiều xe nhất
bai_xe.find_most_common_vehicle_type()

# 6. Tìm loại xe X trong bãi xe
bai_xe.find_vehicle_by_type("Oto")

# 7. Thống kê xe theo đơn giá gởi
bai_xe.statistics_by_don_gia()

# 8. Đếm số lượng xe theo từng loại xe
bai_xe.count_by_vehicle_type()

# 9. Xóa xe X ra khỏi bãi xe
bai_xe.remove_vehicle("79A-12345")

# 10. Đếm tổng số xe gởi của bãi xe
bai_xe.count_vehicles()

# 11. Thống kê doanh thu theo ngày/Tuần/Tháng/Quý/Năm
start_date = datetime.datetime(2024, 8, 1)
end_date = datetime.datetime(2024, 8, 10)
bai_xe.calculate_revenue(start_date, end_date)

# Ghi dữ liệu ra file
bai_xe.write_to_file('xe_data_output.txt')
