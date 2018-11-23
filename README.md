# Sudoku
Project này Mô tả cách xây dựng các chương trình cho bài toán Sudoku. Được viết bằng C++ 
Tạo Class sudoku với
## Các thuộc tính
  1. Lưới -> kiễu mảng 2 chiều gồm 9x9 = 81 ô
    Mỗi ô gồm: Giá trị + Màu sắc
    Giá trị : 1-9
    Màu : màu trắng (màu mặc định, màu đỏ màu đại diện cho giá trị không thể thay đổi được)
  2. Level -> kiểu số nguyên không dấu 
    Có giá trị từ 0 đến 81. tuy trong phần này chỉ tính 3 cấp sudoku là 15 20 25 tương ứng vơi số ô được sinh ra ngẫu nhiên trong lưới
## Các phương thức
  1. Xây dựng mặc nhiên. 
    Khởi tạo các giá trị của ô là 1
    Khởi tạo level là 0 (chưa có ô nào được sinh ra)
    Khởi tạo màu sắc mặc đinh là màu trắng
  3. Hủy
    Giải phóng Sudoku
  4. Kiểm tra hàng
    Gồm 2 đối số vị trí hàng x và giá trị z
    Tìm z trên hàng x. Tìm thấy z trả về false (không hợp lệ) Nếu không tìm thấy trả về true(hợp lệ)
  5. Kiểm tra cột
    Gồm 2 đối số vị trí cột y và giá trị z
    Tìm z trên cột. Nếu tìm thấy z trả về false (không hợp lệ). Nếu không tìm thấy trả về true(hợp lệ)
  6. Kiểm tra lô chứa ô x,y
    Gồm 3 đối số vị trí hàng x, cột y và giá trị z
    xác định các ô đầu tiên của 9 lô qua công thức x=x-x%3 y=y-y%3
    Tìm z trên lô bắt đầu từ ô x,y nếu tìm đươc z thì trả về false (không hợp lên) ngược lại trả về hợp lệ
  7. Kiểm tra hợp lệ
    Trả về true nêu kiểm tra hàng , cột , lô đều là true
    Trả về false trong trường hợp ngược lại
  8. Sinh Ngẫu nhiên
    Sinh ngẫu nhiên vị trí x,y
    Sinh ngẫu nhiên giá trị z
    Nếu ô(x,y) chưa có giá trị và giá trị z là hợp lệ thì thêm z vào ô x,y
  9. Kiểm tra ô trống
    Có 2 đối số. x,y tộ độ 1 ô nào đó.
    Lấy tọa độ ô trống kế tiếp x,y. Nếu lấy được trả về true, không lấy được trả về false
  10. Người chơi
    Yêu cầu người chơi nhập vào 3 giá trị: x,y,z
    Nếu 1 trong 3 giá trị là -1 sẽ thoát khỏi chương trình
    Nếu giá trị nhập vào là hợp lệ. tọa độ trong khoảng 0..8 giá trị ô cần thiếp lập là 0..9 thì 
    Nếu ô x,y hợp lệ (ô có màu trắng)
      Nếu hợp lệ thì thêm z vào ô x,y
      Không hợp lệ báo chính xác vi phạm ràng buộc nào
    Nếu không còn ô trống thì thoát
  11. Máy chơi
    Có 2 đối số x,y
    Ban đầu x=0,y=0;
    1. Nếu không còn được ô trống kếu tiếp ô x,y thì trả về true ngược là thực hiện 2.
    2. Lấy 1 giá trị z trong miền giá trị (1..9). Nếu z hợp lệ thì gán cho ô(x,y) và thực hiện đệ quy đối với ô trống kế tiếp. Nếu không có z nào hợp lệ trả về giá trị false
    3. Nếu giá trị là false thì tiến hành quay lui để thay đổi phương án trước đó
  12. Hiển thị
    Hiển thị chỉ mục hàng, cột vào các dấu để ngăn các các lô với nhau. 
    Màu sắc của các ô cố định là màu đỏ các ô khác là màu trắng
  13. Làm sạch
    Xóa tất các các phần tử trong ô
  ### Quá tải toán tử
       - Quá tải toán tử gán =
          Sao chép các thuộc tính từ một sudoku khác
       - Quá tải toán tử nhập >>
            lặp 81 lần
            Nếu z là số thì gán ô tương ứng có giá trị z ngược lại z='.' gán ô tương ứng là 0
       - Quá tải toán tử xuất <<
             xuất 3 giá trị x,y,z là đáp án của sudoku
        
  ### menu
  0.    Thoát 
  1.    Hiển Thị sudoku
  2.    Chọn level
  - Level 1 --> 25
  - Level 2 --> 20
  - Level 3 --> 15
  - Tùy chỉnh
  3.    Người chơi sudoku
  4.    Máy chơi sudoku
  5.    Sinh mới sudoku
  6.    Nhập sudoku
  7.    Xuất sudoku
