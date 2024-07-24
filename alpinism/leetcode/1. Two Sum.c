
/*
en:
    Given an array of integers, return indices of the two numbers such that they add up to a specific target.

    You may assume that each input would have exactly one solution, and you may not use the same element twice.

    Example:

    Given nums = [2, 7, 11, 15], target = 9,

    Because nums[0] + nums[1] = 2 + 7 = 9,
    return [0, 1].

zh-cn:
    给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
    你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
示例:
    给定 nums = [2, 7, 11, 15], target = 9
    因为 nums[0] + nums[1] = 2 + 7 = 9
    所以返回 [0, 1]

  
Note: The returned array must be malloced, assume caller calls free().
*/
#include <stdio.h>
#include <stdlib.h>
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    int *res = (int *)malloc(sizeof(int) * 2);
    *returnSize = 0;
    for (int i = 0; i < numsSize - 1; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if (nums[i] + nums[j] == target)
            {
                res[0] = i;
                res[1] = j;
                *returnSize = 2;
                return res;
            }
        }
    }
}

int main(int *argc, char **argv)
{
    int nums[4] = {2, 7, 11, 15};
    int *returnSize;
    twoSum(nums, 4, 9, returnSize);
    return 0;
}
