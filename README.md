# SDL2_Game
*Lớp: INT2215_1
*Khóa: K65-UET-VNU

1. Hướng dẫn cài đặt
* Link hướng dẫn cài đặt và chạy demo game: http://www.youtube.com/watch?v=Y88k8PPJm7Y
* Các thư viện SDL2 đã dùng
	- SDL2:[https://www.libsdl.org/download-2.0.php] (Thư viện chung của SDL2)
	- SDL2_image:[https://www.libsdl.org/projects/SDL_image/] (Thư viện tải hình ảnh và đồ họa)
	- SDL2_ttf:[https://www.libsdl.org/projects/SDL_ttf/] (Thư viện tải font chữ cho text)
	- SDL2_mixer:[https://www.libsdl.org/projects/SDL_mixer/] (Thư viện tải âm thanh)

2. Thuật toán của game:
	- Một bảng gồm 22 ô chiều cao và 15 ô chiều rộng
	- Tất cả các ô trong bảng có giá trị 0, các khối hình có chỉ số từ 1 đến 5, nếu xếp gặp các số 
khác 0 thì dừng lại (xử lý va chạm)
	- Tạo khối bằng cách rand ngẫu nhiên chỉ số khối, đồng thời tạo bóng từ khối vừa tạo
	- Nếu nhận được phím điều khiển từ bàn phím:
		+ Xóa khối, bóng ở vị trí cũ
		+ Xử lý
		+ Cập nhập lại tình hình khối, bóng sau khi xử lý
	- Kiểm tra đi xuống:
		+ Nếu đi xuống, xóa cũ, vẽ mới
		+ In ra bảng mới
	- Nếu thua đi đến màn hình gameOver và có các tùy chọn replay hoặc home
	- Nếu click vào tạm dừng, có các tùy chọn replay, continue hoặc home

3. Cách chơi game
* Luật chơi
	- Các khối được sinh ra ngẫu nhiên và rơi xuống đến vị trí tối đa.(tốc độ rơi nhanh hay chậm tùy thuộc vào level, level càng cao thì tốc độ càng nhanh)
	- Nhiệm vụ của người chơi là di chuyển khối sang trái, phải hoặc xoay khối theo các góc 0 độ, 90 độ, 180 độ, 270 độ để khối hình rơi vào vị trí tốt nhất, với mục đích lấp đầy các hàng, khi đó các hàng đã được lấp đầy sẽ biến mất và điểm sẽ được cộng.
	- Công thức tính điểm: 
 		+ Số hàng biến mất = 1 => + 100;
		+ Số hàng biến mất >=2 => + (số hàng biến mất * 115);
	- Game sẽ kết thúc khi có khối chạm nóc
	- Trong quá trình chơi, người chơi có thể click chuột vào pause để tạm dừng game, sau đó có thể chọn replay để bắt đầu lại, continue để tiếp tục hoặc home để quay trở lại menu.
* Cách điểu khiển các phím
	- Sử dụng các phím mũi tên trái, phải để điều chỉnh khối, mũi tên hướng lên để xoay khối và mũi tên hướng xuống để đưa khối rơi xuống nhanh hơn, phím Space để khối rơi xuống vị trí tối đa ngay lập tức
	- Khi khối vừa rơi xuống vị trí tối đa, người chơi có thể ngay lập tức điều chỉnh sang trái hoặc phải, với điều kiện là nơi đẩy khối vào vẫn còn chỗ trống

	
