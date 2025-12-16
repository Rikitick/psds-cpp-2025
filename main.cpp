#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>

struct Date {
    unsigned year;
    unsigned month;
    unsigned day;

    Date (unsigned y = 0u, unsigned m = 0u, unsigned d = 0u) : year(y), month(m), day(d) {}
};

bool operator==(const Date& leftDate, const Date& rightDate) {
    return std::tie(leftDate.year, leftDate.month, leftDate.day) == std::tie(rightDate.year, rightDate.month, rightDate.day);
}

bool operator!=(const Date& leftDate, const Date& rightDate) {
    return !(leftDate == rightDate);
}

bool operator<(const Date& leftDate, const Date& rightDate) {
    return std::tie(leftDate.year, leftDate.month, leftDate.day) < std::tie(rightDate.year, rightDate.month, rightDate.day);
}

bool operator>(const Date& leftDate, const Date& rightDate) {
    return rightDate < leftDate;
}

bool operator<=(const Date& leftDate, const Date& rightDate) {
    return leftDate < rightDate || leftDate == rightDate;
}

bool operator>=(const Date& leftDate, const Date& rightDate) {
    return leftDate > rightDate || leftDate == rightDate;
}

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

bool operator==(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return std::tie(leftStudent.mark, leftStudent.score) == std::tie(rightStudent.mark, rightStudent.score);
}

bool operator!=(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return !(leftStudent == rightStudent);
}

bool operator<(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    if (leftStudent.mark != rightStudent.mark)
        return leftStudent.mark > rightStudent.mark;
    if (leftStudent.score != rightStudent.score)
        return leftStudent.score < rightStudent.score;
    if (leftStudent.course != rightStudent.course)
        return leftStudent.course > rightStudent.course;
    if (leftStudent.birth_date != rightStudent.birth_date)
        return leftStudent.birth_date < rightStudent.birth_date;
    return false;
}

bool operator>(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return rightStudent < leftStudent;
}

bool operator<=(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return leftStudent < rightStudent || leftStudent == rightStudent;
}

bool operator>=(const StudentInfo& leftStudent, const StudentInfo& rightStudent) {
    return leftStudent > rightStudent || leftStudent == rightStudent;
}

int main(void) {
    std::vector<StudentInfo> students = {
        {1, 'A', 2000, 5, Date{2000, 1, 1}},
        {2, 'A', 1999, 1, Date{2004, 2, 1}},
        {3, 'A', 1999, 1, Date{2003, 2, 1}},
        {4, 'B', 150, 5, Date{2017, 1, 1}},
        {5, 'C', 140, 3, Date{2016, 1, 1}},
        {6, 'D', 120, 2, Date{2017, 1, 1}},
        {7, 'Z', 100, 1, Date{2018, 1, 1}},
        {8, 'A', 1999, 2, Date{2003, 1, 1}},
        {9, 'A', 1999, 1, Date{2003, 1, 1}},
        {10, 'A', 2000, 4, Date{2000, 1, 1}},
        {11, 'A', 2000, 4, Date{2000, 1, 2}}
    };

    std::sort(students.begin(), students.end());

    for (size_t i = 0; i < students.size(); ++i) {
        std::cout << students[i].id << ' ' << students[i].mark << ' ' << students[i].score << ' ' << students[i].course << ' ' << students[i].birth_date.year << '\n';
    }
    return 0;
}