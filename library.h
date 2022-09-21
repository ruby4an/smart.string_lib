#include <iostream>
#include <cstdlib>

using namespace std;

#define SSO_SIZE 50

class SmartString {
public:
    explicit SmartString(const char *string);

    const char *to_c_str();

    SmartString(SmartString &string);

    SmartString operator+=(const SmartString &obj);

    SmartString operator+=(const char *obj);

    SmartString operator+=(char obj);

    char *operator+(const SmartString &obj);

    char *operator+(const char *obj);

    char *operator+(char obj);

    SmartString operator=(const SmartString &obj);

    SmartString operator=(const char *obj);

    SmartString append(const SmartString &obj);

    SmartString append(char obj);

    SmartString append(const char *obj);

    char operator[](int idx);

    SmartString toUpper();

    SmartString toLower();

    SmartString replace(const char *replaced, const char *replacing);

private:
    size_t lenght;
    char *content;
    char cont_SSO[SSO_SIZE];
    char *cont;

    int find_amount(const char *obj);

    static size_t get_char_size(const char *obj);

    static int switch_to_dynamic(size_t whole_len, size_t whole_diff);

    static int switch_to_static(size_t whole_len, size_t whole_diff);

    static int keep_dynamic(size_t whole_len, size_t whole_diff);
};
