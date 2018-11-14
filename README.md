# Sudoku
Project này trình bày những vấn đề cơ bản về Sudoku. Project được viết bằng C++
Ban đầu ta tao ra một Class với những thuộc tính như:
* Một bảng có kích thước 9x9 tức là 81 ô
  - Mỗi một ô gồm có 2 thuộc tính là giá trị của ô đó. có miền giá trị từ 1..9 và Màu của ô
  + Màu của ô gồm 2 màu là màu cố định và màu mặc định màu. Màu cố định biểu thị các giá trị trong ô là không được phép thay đổi khi giải sudoku. Chúng cũng giúp cho ta dễ dàng phân biệt với những giá trị mà ta cần thiếp lập với ô không được phép thiếp lập giá trị cho chúng
* 3 Mảng 1 chiều với 9 phần tử. markrow,markcol,markblock dùng để đánh dấu các phần tử có giá trị z trong hàng x, trong cột y và trong vùng x/3*(3)+y/3. với x,y tương ứng là chỉ số hàng và chỉ số cột của một ô cần nhập giá trị z. công thức x/3*(3)+y/3 dùng để tính chỉ số lô cần đánh dấu.
* Level đại diện cho mức độ khó của sudoku. khi sinh sukoku ta dựa vào level để sinh ra số lượng phần tử tương ứng. level càng cao thì sinh ra càng nhiều giá trị khi đó mức độ sẽ càng dễ đối với người chơi. level càng thấp tức là số lượng giá trị được sinh ra càng ít, càng khó để cho người chơi giải quyết. tuy nhiên nếu level càng cao thì sinh sudoku có thể sẽ rất lâu, và có thể sudoku được sinh ra sẽ không thể tìm ra lời giải nào.

Class có các phương thức như sau:
* Phương thức xây dựng mặc nhiên. 
    - Làm sạch tất các các thuộc tính của sudoku
* Phương thức xây dựng sao chép
    - Sao chép các thuộc tính từ một sudoku khác
* Phương thức hủy 
    - Loại bỏ đối tượng sudoku
* Phương thức sinh ngẫu nhiên các giá trị của sudoku
  1. Sinh ngẫu nhiên vị trí x,y,d
  2. Nếu ô x,y trống thực hiện sinh tuần tự đố với z từ 1+ 1 .. 9 + d % 9
    2.1. Kiểm tra giá trị z có hợp lệ hay không 
      2.1.1. Nếu không: nếu không làm mới sudoku đến bước 3
      2.1.1. Nếu có: đặt giá trị mới vào ô trống x,y đến bước 3
  3. Lặp lại bước 1 đến khi số lượng sinh ra bằng đúng level của sudoku
* Phương thưc kiểm tra hợp lệ
  - Tham só vào x,y,z 
  - Giá trị trả về là true nếu z không nằm trong hàng x, z không nằm trong cột y và z không nằm trong lô x/3* 3+y/3
  - Giá trị trả về là false trong trường hợp ngược lại
* Phương thức đặt giá trị vào ô x,y
  - Tham số vào gồm x,y,z
  - Đặt z vào ô x,y
  - Đánh dấu bít thứ z của 3 mảng 1 chiều
* Phương thức xóa giá trị ô x,y
  - Đưa về giá trị 0
  - Xóa đánh dấu vị trị z trong 3 mảng 1 chiều
* Phương thưc người chơi giải quyết sudoku
  - Cho phép người chơi nhập vào 3 giá trị
  - Nếu giá trị nhập vào là -1 thì kết thúc
  - Nếu giá trị không phải là -1 thì nhận vào 3 tham số
  - Nếu giá trị nhập vào là hợp lệ. tọa độ trong khoảng 0..8 giá trị ô cần thiếp lập là 0..9 thì 
  + Nếu tọa độ x,y hợp lệ (ô có màu mặt đinh)
  ++ Nếu giá trị là 0 thì xóa ô đó
  ++ Người lại kiểm tra giá trị hợp lệ
  +++ Nếu hợp lệ thì xóa giá trị cũ,đặt giá trị mới vào ô
  +++ Nếu không hợp lệ thì thông báo lỗi 
  - Nếu tất cả các ô đều được đánh dấu thì thông báo đã hoàn thành (các giá trị trong hàng hoặc cột hoặc lô bằng 511)
* Phương thức máy giải quyết sudoku
  - Nhận vào 2 tham số x,y là ô hiện tại đang giải quyết
  - Trả về giá trị true nếu như vấn đề đã được giải quyết
  - Vấn đề đã được giả quyết khi không còn ô trống nào
  - Trả về giá trị false nếu nhưng không tìm được giải pháp
  - Giải Thuật Quay Lui
    1.Lấy ô trống kế tiếp ô x,y
    2.Nếu như còn ô trống thì lần lượt xét các giá trị từ 1 đền 9 cho ô trống đó
    3.Nếu giá trị hợp lệ thì đặt giá trị vào ô
    4.Thực hiện đệ quy đối với ô trống kế tiếp. Nếu
    4.1 Không thể đi tiếp thì Quay lui lại (Xóa ô hiện tại) thực hiên với giá trị tiếp theo
    4.2 Có thể đi tiếp thực hiện đệ quy
    4.3 Tìm thấy kết quả dừng chương trình
* Phương thức hiển thị
  - Hiển thị dòng chỉ mục cột
  - Hiển thị dòng ngăn các lô
  - Hiển thị các chỉ mục dòng các giá trị sudou và Biên ngăn các lô
  - Hiển thị màu cố định đối với các số đã sinh
