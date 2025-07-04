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
    PENDING,
    PREPARING,
    READY,
    DELIVERED,
    CANCELLED
};




// دسته‌بندی غذاها
enum class FoodCategory {
    FAST_FOOD,
    IRANIAN,
    PIZZA,
    APPETIZER,
    MAIN_COURSE,
    DRINKS,
    DESSERT
};




enum class Role {
    Customer,
    RestaurantOwner,
    Admin
};

#endif // ENUMS_H


