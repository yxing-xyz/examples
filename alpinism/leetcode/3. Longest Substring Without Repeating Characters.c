
/*

en:
    Given a string, find the length of the longest substring without repeating characters.

    Example 1:

    Input: "abcabcbb"
    Output: 3 
    Explanation: The answer is "abc", with the length of 3. 
    Example 2:

    Input: "bbbbb"
    Output: 1
    Explanation: The answer is "b", with the length of 1.
    Example 3:

    Input: "pwwkew"
    Output: 3
    Explanation: The answer is "wke", with the length of 3. 
                Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

zh-cn:
    给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例:
    输入: "abcabcbb"
    输出: 3 
    解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

    输入: "bbbbb"
    输出: 1
    解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

    输入: "pwwkew"
    输出: 3
    解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
         请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
  
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int lengthOfLongestSubstring_my(char *s)
{
    int i, j, max_len, cur_len = 0, str_len = strlen(s);
    char map[256];
    memset(map, 0, 256);
    for (i = 0; i < str_len; i++)
    {
        cur_len = 1;
        map[s[i]] = true;
        for (j = i + 1; j < str_len; j++)
        {
            if (map[s[j]])
            {
                break;
            }
            cur_len += 1;
            map[s[j]] = true;
        }
        max_len = max_len > cur_len ? max_len : cur_len;
        memset(map, 0, 256);
    }
    return max_len;
}

/*
算法：
思路：将n个字符划分为前n-1个字符和第n个字符两个子集，当遍历第n个字符时，显然，前n-1个字符中无重复的最长子串长度是已知的（不妨设为prior），
要确定n个字符所构成的字符串中无重复的最长子串长度，只需要再确定这n个包含第n个字符的字符串中无重复的最长子串长度（不妨设为len），
max{prior, len}即为n个字符中无重复的最长子串长度（手动狗头，感觉有点数学归纳法证明不等式的味道，捂脸😀这个算法我憋了两天才想到，纪念一下）

如果是其他编码格式的请使用hashmap节省空间、转成多字节编码统一转成unicode
*/

int lengthOfLongestSubstring(char *s)
{
    // max 最大值
    // start 开始的索引位置
    // next 下一个字符的索引位置
    // next - start = 当前字符 + 1 - 开始索引位 = 长度
    // map作用：重复后找出开始索引的下一个索引位置，因为存放的是next
    int max=0, start = 0, next = 1;
    int map[128] = {0}; // 小心： 1、key溢出128、多字节会溢出。2、存储的索引值溢出
    for (; *s != '\0'; s++, next++)
    {
        if (map[*s] > start)
        {
            start = map[*s];
        }

        map[*s] = next;
        max = (max >= next - start) ? max : (next - start);
    }
    return max;
}

int main(int *argc, char **argv)
{
    printf("rt %d\n", lengthOfLongestSubstring("阿迪斯发士大夫"));
    return 0;
}
