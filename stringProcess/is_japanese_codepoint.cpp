#include <iostream>
#include <string>
#include <cstdint> // 用于uint32_t
#include <cstring> // 用于strlen

// 错误码定义（可选，用于调试）
enum class UTF8ParseError {
    OK,
    INVALID_LEADING_BYTE, // 无效的起始字节
    INVALID_CONTINUATION_BYTE, // 无效的续字节
    INCOMPLETE_SEQUENCE, // 不完整的UTF8序列
    OVERLONG_ENCODING, // 过长编码（如单字节能表示却用多字节）
    CODEPOINT_OUT_OF_RANGE // 码点超出Unicode范围（>U+10FFFF）
};

/**
 * @brief 解析UTF8字符，转换为Unicode码点
 * @param str 指向UTF8字符串的指针（引用，解析后指针移动到下一个字符）
 * @param len 剩余字符串长度（防止越界）
 * @param codepoint 输出：解析出的Unicode码点
 * @return 解析结果（OK表示成功）
 */
UTF8ParseError utf8_to_codepoint(const char*& str, size_t& len, uint32_t& codepoint) {
    if (len == 0) {
        return UTF8ParseError::INCOMPLETE_SEQUENCE;
    }

    // 第一步：获取起始字节，判断UTF8字符长度
    unsigned char leading_byte = static_cast<unsigned char>(*str);
    int utf8_len = 0;
    uint32_t min_codepoint = 0;

    if ((leading_byte & 0x80) == 0) { // 0xxxxxxx：1字节UTF8（ASCII）
        utf8_len = 1;
        min_codepoint = 0;
        codepoint = leading_byte;
    } else if ((leading_byte & 0xE0) == 0xC0) { // 110xxxxx：2字节UTF8
        utf8_len = 2;
        min_codepoint = 0x80;
        codepoint = leading_byte & 0x1F;
    } else if ((leading_byte & 0xF0) == 0xE0) { // 1110xxxx：3字节UTF8
        utf8_len = 3;
        min_codepoint = 0x800;
        codepoint = leading_byte & 0x0F;
    } else if ((leading_byte & 0xF8) == 0xF0) { // 11110xxx：4字节UTF8
        utf8_len = 4;
        min_codepoint = 0x10000;
        codepoint = leading_byte & 0x07;
    } else {
        return UTF8ParseError::INVALID_LEADING_BYTE; // 无效的起始字节
    }

    // 检查剩余长度是否足够
    if (utf8_len > len) {
        return UTF8ParseError::INCOMPLETE_SEQUENCE;
    }

    // 第二步：解析续字节（10xxxxxx）
    for (int i = 1; i < utf8_len; ++i) {
        str++;
        len--;
        unsigned char cont_byte = static_cast<unsigned char>(*str);
        if ((cont_byte & 0xC0) != 0x80) { // 续字节必须以10开头
            return UTF8ParseError::INVALID_CONTINUATION_BYTE;
        }
        codepoint = (codepoint << 6) | (cont_byte & 0x3F);
    }

    // 第三步：校验码点合法性
    if (codepoint < min_codepoint) {
        return UTF8ParseError::OVERLONG_ENCODING; // 过长编码
    }
    if (codepoint > 0x10FFFF) { // Unicode最大码点是U+10FFFF
        return UTF8ParseError::CODEPOINT_OUT_OF_RANGE;
    }

    // 移动指针到下一个字符的起始位置
    str++;
    len--;
    return UTF8ParseError::OK;
}

/**
 * @brief 判断单个Unicode码点是否为日语字符
 * @param codepoint Unicode码点
 * @return true=是日语字符，false=否
 */
bool is_japanese_codepoint(uint32_t codepoint) {
    // 覆盖日语核心字符范围
    return (codepoint >= 0x3000 && codepoint <= 0x30FF) || // 平假名、片假名、日文标点
           (codepoint >= 0xFF65 && codepoint <= 0xFF9F) || // 半角片假名
           (codepoint >= 0xFF01 && codepoint <= 0xFF5E) || // 全角ASCII符号（日语常用）
           (codepoint >= 0x4E00 && codepoint <= 0x9FFF);   // 日文汉字（中日韩统一汉字）
}

/**
 * @brief 判断UTF8字符串是否为日语（核心逻辑：所有字符均为日语字符）
 * @param utf8_str UTF8编码的字符串
 * @param allow_mixed_ascii 是否允许混合半角ASCII（如数字/字母，默认不允许）
 * @return true=是日语字符串，false=否
 */
bool is_japanese_utf8(const std::string& utf8_str, bool allow_mixed_ascii = false) {
    const char* str = utf8_str.c_str();
    size_t len = strlen(str);

    // 空字符串直接返回false
    if (len == 0) {
        return false;
    }

    while (len > 0) {
        uint32_t codepoint = 0;
        UTF8ParseError err = utf8_to_codepoint(str, len, codepoint);

        // 解析UTF8失败，判定为非日语
        if (err != UTF8ParseError::OK) {
            std::cerr << "UTF8解析错误：" << static_cast<int>(err) << std::endl;
            return false;
        }

        // 判断码点是否为日语字符
        bool is_jp = is_japanese_codepoint(codepoint);
        
        // 允许混合半角ASCII的情况：ASCII字符（U+0020~U+007E）不判定为非日语
        if (allow_mixed_ascii && (codepoint >= 0x20 && codepoint <= 0x7E)) {
            continue;
        }

        // 存在非日语字符，直接返回false
        if (!is_jp) {
            return false;
        }
    }

    // 所有字符均为日语字符
    return true;
}

// 测试示例
int main() {
    // 测试用例1：纯日语（平假名+汉字+标点）
    std::string jp_str1 = u8"こんにちは、世界！"; // UTF8编码的日语
    std::cout << "测试用例1：" << (is_japanese_utf8(jp_str1) ? "是日语" : "非日语") << std::endl;

    // 测试用例2：混合全角ASCII（日语中常用）
    std::string jp_str2 = u8"日本のGDPは5兆円です（2024年）";
    std::cout << "测试用例2：" << (is_japanese_utf8(jp_str2) ? "是日语" : "非日语") << std::endl;

    // 测试用例3：混合半角ASCII（默认不允许）
    std::string jp_str3 = u8"こんにちは 123";
    std::cout << "测试用例3（默认）：" << (is_japanese_utf8(jp_str3) ? "是日语" : "非日语") << std::endl;
    std::cout << "测试用例3（允许半角ASCII）：" << (is_japanese_utf8(jp_str3, true) ? "是日语" : "非日语") << std::endl;

    // 测试用例4：非日语（中文）
    std::string cn_str = u8"你好，世界！";
    std::cout << "测试用例4：" << (is_japanese_utf8(cn_str) ? "是日语" : "非日语") << std::endl;

    // 测试用例5：非日语（英文）
    std::string en_str = "Hello World!";
    std::cout << "测试用例5：" << (is_japanese_utf8(en_str) ? "是日语" : "非日语") << std::endl;

    return 0;
}
