/*
 * File: constants.h
 * Description: Chứa các hằng số cấu hình và mã lỗi cho Task 1
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// --- 1. Cấu hình Mặc định (Default Configuration) ---
// Nếu người dùng không nhập tham số, dùng các giá trị này
#define DEFAULT_NUM_SENSORS 1       // Mặc định 1 cảm biến [cite: 6]
#define DEFAULT_SAMPLING_SEC 60     // Mặc định 60 giây [cite: 10]
#define DEFAULT_INTERVAL_HRS 24     // Mặc định 24 giờ [cite: 13]

// --- 2. Ràng buộc Đầu vào (Input Constraints) ---
// Giá trị nhỏ nhất cho phép để tránh lỗi logic
#define MIN_SAMPLING_SEC 1          // Tối thiểu 1 giây [cite: 8]
#define MIN_INTERVAL_HRS 1          // Tối thiểu 1 giờ [cite: 12]

// --- 3. Thông số Cảm biến (Sensor Specs) ---
// Dùng để sinh dữ liệu ngẫu nhiên (Random Generation)
#define TEMP_MIN -40.0              // Nhiệt độ thấp nhất [cite: 2]
#define TEMP_MAX 125.0              // Nhiệt độ cao nhất [cite: 2]
#define TEMP_PRECISION 0.1          // Độ chính xác 1 số lẻ (đề yêu cầu 1 chữ số sau dấu phẩy) [cite: 19]

#define HUM_MIN 5                   // Độ ẩm thấp nhất (%) [cite: 2]
#define HUM_MAX 100                 // Độ ẩm cao nhất (%) [cite: 2]
// --- 4. Định nghĩa Mã lỗi (Error Codes) ---
// Dùng enum để code dễ đọc thay vì nhớ số 01, 02...
enum ErrorCode {
    SUCCESS = 0,
    
    // Task 1 Errors
    ERR_INVALID_COMMAND = 1,        // Error 01: Câu lệnh sai/thiếu tham số [cite: 75]
    ERR_INVALID_ARGUMENT = 2,       // Error 02: Giá trị tham số không hợp lệ (< 0) [cite: 77]
    ERR_FILE_ACCESS_DENIED = 3      // Error 03: Không mở/ghi được file [cite: 78]
};

#endif // CONSTANTS_H