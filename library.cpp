#include "library.h"


size_t SmartString::get_char_size(const char *obj) {
    size_t size = 0;
    size_t idx = 0;
    while (obj[idx] != '\0') {
        size++;
        idx++;
    }
    return size;
}

SmartString::SmartString(const char *string) {
    if (get_char_size(string) > SSO_SIZE) {
        int idx = 0;
        lenght = get_char_size(string);
        cont = (char *) calloc(lenght + 1, sizeof(char));

        if (cont == nullptr) {
            exit(1);
        }
        for (int i = 0; i < lenght; i++) {
            cont[i] = string[i];
        }
        cont[lenght] = '\0';
        content = cont;
    } else {
        lenght = get_char_size(string);
        for (size_t i = 0; i < get_char_size(string); i++) {
            cont_SSO[i] = string[i];
        }
        cont_SSO[get_char_size(string)] = '\0';
        content = cont_SSO;
        cont = nullptr;
    }
}

const char *SmartString::to_c_str() {
    return (const char *) content;
}

SmartString SmartString::operator+=(const SmartString &obj) {
    size_t lenght_strs = this->lenght + obj.lenght;
    size_t len = this->lenght;
    char copied_str[len];
    for (size_t i = 0; i < this->lenght; i++) {
        copied_str[i] = this->content[i];
    }
    if (lenght_strs > SSO_SIZE) {
        if (len > SSO_SIZE) {
            free(this->content);
        } else {
            fill_n(this->cont_SSO, SSO_SIZE, 0);
        }
        this->cont = (char *) calloc(lenght_strs + 1, sizeof(char));
        this->content = this->cont;
        if (this->content == nullptr) {
            exit(1);
        }
        for (size_t i = 0; i < len; i++) {
            this->content[i] = copied_str[i];
        }
        for (size_t i = len; i < lenght_strs; i++) {
            this->lenght++;
            this->content[i] = obj.content[i - len];
        }
        this->content[lenght_strs + 1] = '\0';
    } else {
        for (size_t idx = len; idx < lenght_strs; idx++) {
            this->content[idx] = obj.content[idx];
        }
        this->content[lenght_strs] = '\0';
    }
    return *this;
}

SmartString SmartString::operator+=(const char *obj) {
    size_t obj_len = get_char_size(obj);
    size_t len = this->lenght;
    size_t lenght_strs = len + obj_len;
    char copied_str[this->lenght];
    for (size_t i = 0; i < this->lenght; i++) {
        copied_str[i] = this->content[i];
    }
    if (lenght_strs > SSO_SIZE) {
        if (len > SSO_SIZE) {
            free(this->content);
        } else {
            fill_n(this->cont_SSO, SSO_SIZE, 0);
        }
        this->cont = (char *) calloc(lenght_strs + 1, sizeof(char));
        this->content = this->cont;
        if (this->content == nullptr) {
            exit(1);
        }
        for (size_t i = 0; i < len; i++) {
            this->content[i] = copied_str[i];
        }
        for (size_t i = len; i < lenght_strs; i++) {
            this->content[i] = obj[i - len];
            this->lenght++;
        }
        this->content[this->lenght] = '\0';
    } else {
        for (size_t idx = len; idx < lenght_strs; idx++) {
            this->content[idx] = obj[idx - len];
        }
        this->content[lenght_strs] = '\0';
    }
    return *this;
}

SmartString SmartString::operator+=(char obj) {
    size_t len = this->lenght;
    size_t lenght_strs = len + 1;

    if (lenght_strs > SSO_SIZE) {
        char copied_str[len];
        for (size_t i = 0; i < len; i++) {
            copied_str[i] = this->content[i];
        }
        copied_str[len] = '\0';
        if (len > SSO_SIZE) {
            free(this->content);
        } else {
            fill_n(this->cont_SSO, SSO_SIZE, 0);
        }
        this->cont = (char *) calloc(len + 2, sizeof(char));
        this->content = this->cont;
        if (this->content == nullptr) {
            exit(1);
        }
        for (size_t i = 0; i < len; i++) {
            this->content[i] = copied_str[i];
        }
        this->content[len] = obj;
        this->content[len + 1] = '\0';
        lenght += 1;
    } else {
        this->content[len] = obj;
        this->content[lenght_strs] = '\0';
    }
    return *this;
}

SmartString::SmartString(SmartString &string) {
    lenght = string.lenght;
    if (lenght > SSO_SIZE) {
        this->cont = (char *) calloc(lenght + 1, sizeof(char));
        if (this->cont == nullptr) {
            exit(1);
        }
        this->content = this->cont;
        for (int idx = 0; idx < lenght; idx++) {
            this->content[idx] = string.content[idx];
        }
        this->content[lenght] = '\0';
    } else {
        this->cont = nullptr;
        this->content = this->cont_SSO;
        for (int idx = 0; idx < lenght; idx++) {
            this->content[idx] = string.content[idx];
        }
        this->content[lenght] = '\0';
    }
}

SmartString SmartString::append(const SmartString &obj) {
    *this += obj;
    return *this;
}

SmartString SmartString::append(char obj) {
    *this += obj;
    return *this;
}

SmartString SmartString::append(const char *obj) {
    *this += obj;
    return *this;
}

char SmartString::operator[](int idx) {
    if (idx < this->lenght) {
        return this->content[idx];
    } else if (-this->lenght < idx && idx < 0) {
        return this->content[this->lenght + idx];
    } else {
        cout << "Wrong index input: idx is bigger than size of the string";
        exit(1);
    }
}

SmartString SmartString::toUpper() {
    for (int i = 0; i < lenght; i++) {
        this->content[i] = _toupper(this->content[i]);
    }
    return *this;
}

SmartString SmartString::toLower() {
    for (int i = 0; i < lenght; i++) {
        this->content[i] = _tolower(this->content[i]);
    }
    return *this;
}

SmartString SmartString::replace(const char *replaced, const char *replacing) {
    size_t len = get_char_size(replaced);
    if (!len) {
        cout << "What r u replacing?)";
        exit(1);
    }
    size_t len_replacing = get_char_size(replacing);
    if (len_replacing == len) {
        for (int idx = 0; idx < this->lenght; idx++) {
            int help = idx;
            for (int i = 0; i < len; i++) {
                if (this->content[idx] != replaced[i]) {
                    break;
                } else if (i == len - 1) {
                    if (this->content[idx] == replaced[i]) {
                        for (int ix = 0; ix < len; ix++) {
                            this->content[idx - (len - (ix + 1))] = replacing[ix];
                        }
                    }
                    continue;
                } else {
                    idx++;
                }
            }
            idx = help;

        }
        return *this;

    } else {
        char copy_str[this->lenght + 1];
        for (size_t i = 0; i < this->lenght; i++) {
            copy_str[i] = this->content[i];
        }
        copy_str[lenght] = '\0';
        size_t str_len = this->lenght;
        size_t whole_difference = (len_replacing - len) * this->find_amount(replaced);
        if (switch_to_dynamic(str_len, whole_difference)) {
            fill_n(this->cont_SSO, SSO_SIZE, 0);
            this->cont = (char *) calloc(str_len + (whole_difference + 1), sizeof(char));
            this->content = this->cont;
        } else if (switch_to_static(str_len, whole_difference)) {
            free(this->content);
            this->content = this->cont_SSO;
        } else if (keep_dynamic(str_len, whole_difference)) {
            this->content = (char *) calloc(str_len + (whole_difference + 1), sizeof(char));
        }
        if (this->content == nullptr) {
            exit(1);
        }
        size_t diff = 0;
        for (int idx = 0; idx < str_len; idx++) {
            for (int i = 0; i < len; i++) {
                if (copy_str[idx] != replaced[i]) {
                    this->content[idx + diff] = copy_str[idx];
                    break;
                } else if (i == len - 1) {
                    for (int ix = 0; ix < len_replacing; ix++) {
                        this->content[idx - (len - (ix + diff + 1))] = replacing[ix];
                    }
                    this->lenght += (len_replacing - len);
                    diff += (len_replacing - len);
                    continue;
                } else {
                    idx++;
                }
            }
        }
        this->content[lenght] = '\0';
        return *this;
    }

}

int SmartString::find_amount(const char *obj) {
    int idx = 0;
    int len = 0;
    int amount = 0;
    while (obj[idx] != '\0') {
        idx++;
        len++;
    }
    for (idx = 0; idx < this->lenght; idx++) {
        int help = idx;
        for (int i = 0; i < len; i++) {
            if (this->content[idx] != obj[i]) {
                break;
            } else if (i == len - 1) {
                amount++;
                continue;
            } else {
                idx++;
            }

        }
    }
    return amount;
}

int SmartString::switch_to_dynamic(size_t whole_len, size_t whole_diff) {
    if (whole_len <= SSO_SIZE && whole_len + whole_diff > SSO_SIZE) {
        return 1;
    } else {
        return 0;
    }
}

int SmartString::switch_to_static(size_t whole_len, size_t whole_diff) {
    if (whole_len > SSO_SIZE && whole_len + whole_diff <= SSO_SIZE) {
        return 1;
    } else {
        return 0;
    }
}

int SmartString::keep_dynamic(size_t whole_len, size_t whole_diff) {
    if (whole_len > SSO_SIZE && whole_len + whole_diff > SSO_SIZE) {
        return 1;
    } else {
        return 0;
    }
}

SmartString SmartString::operator=(const SmartString &obj) {
    if (this->lenght > SSO_SIZE) {
        free(this->content);
    } else {
        fill_n(this->cont_SSO, SSO_SIZE, 0);
    }
    lenght = obj.lenght;
    if (lenght > SSO_SIZE) {
        this->cont = (char *) calloc(lenght + 1, sizeof(char));
        if (this->cont == nullptr) {
            exit(1);
        }
        this->content = this->cont;
        for (int idx = 0; idx < lenght; idx++) {
            this->content[idx] = obj.content[idx];
        }
        this->content[lenght] = '\0';
    } else {
        free(this->cont);
        this->content = this->cont_SSO;
        for (int idx = 0; idx < lenght; idx++) {
            this->content[idx] = obj.content[idx];
        }
        this->content[lenght] = '\0';
    }
    return *this;
}

SmartString SmartString::operator=(const char *obj) {
    if (this->lenght > SSO_SIZE) {
        free(this->content);
    } else {
        fill_n(this->cont_SSO, SSO_SIZE, 0);
    }
    lenght = get_char_size(obj);
    if (lenght > SSO_SIZE) {
        this->cont = (char *) calloc(lenght + 1, sizeof(char));
        if (this->cont == nullptr) {
            exit(1);
        }
        this->content = this->cont;
        for (int idx = 0; idx < lenght; idx++) {
            this->content[idx] = obj[idx];
        }
        this->content[lenght] = '\0';
    } else {
        free(this->cont);
        this->content = this->cont_SSO;
        for (int idx = 0; idx < lenght; idx++) {
            this->content[idx] = obj[idx];
        }
        this->content[lenght] = '\0';
    }
    return *this;
}

char *SmartString::operator+(const SmartString &obj) {
    SmartString new_str(*this);
    new_str += obj;
    return new_str.content;
}

char *SmartString::operator+(const char *obj) {
    SmartString new_str(*this);
    new_str += obj;
    return new_str.content;
}

char *SmartString::operator+(char obj) {
    SmartString new_str(*this);
    new_str += obj;
    return new_str.content;
}
