#ifndef ENUMS_H
#define ENUMS_H

// نوع کاربران سیستم
enum class UserType {
    CUSTOMER,
    RESTAURANT_OWNER,
    ADMIN
};

// وضعیت سفارش‌ها
enum class OrderStatus {
    PENDING,        // در انتظار تأیید
    PREPARING,      // در حال آماده‌سازی
    READY,          // آماده تحویل
    DELIVERED,      // تحویل داده شده
    CANCELLED       // لغو شده
};

// دسته‌بندی غذاها
enum class FoodCategory {
    FAST_FOOD,
    IRANIAN,
    PIZZA,
    DRINKS,
    DESSERT
};

#endif // ENUMS_H
