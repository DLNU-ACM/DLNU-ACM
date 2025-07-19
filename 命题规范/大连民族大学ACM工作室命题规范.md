
# 大连民族大学 ACM 工作室命题规范

为提升工作室题库的质量，采用牛客竞赛平台制定的[牛客系列赛命题规范](https://blog.nowcoder.net/n/6cb53e0afdff48ed8fbc046a077f6649)作为主要参考标准。请各位出题人在命题前务必认真阅读以下资料：

- [oi-wiki 出题](https://oi-wiki.org/contest/problemsetting/)
- [牛客系列赛命题规范](https://blog.nowcoder.net/n/6cb53e0afdff48ed8fbc046a077f6649)
- [牛客平台编写 Special Judge](https://www.nowcoder.com/discuss/353154397968474112)
- [oi-wiki testlib 使用](https://oi-wiki.org/tools/testlib/)
- [Codeforces 平台命题规范](https://docs.google.com/document/d/e/2PACX-1vQb6o41KOv0r0ji90evgzNiBaOWXJXtoy_jUlNHOBxGOdfLfCulWbYd5IaR-tyrmQAn_G1Y3jqY4OF0/pub)

如遇与[牛客系列赛命题规范](https://blog.nowcoder.net/n/6cb53e0afdff48ed8fbc046a077f6649)不一致之处，请优先遵循[牛客系列赛命题规范](https://blog.nowcoder.net/n/6cb53e0afdff48ed8fbc046a077f6649)。

## 命题原则

- 题目必须为原创，不得与已广泛传播的原题重复。
- 对于基础题目，可适当借鉴现有题目思路，但实现代码不得与原题完全一致。
- 对于高难度题目，应尽量避免与现有题目高度相似，严禁以考查常见模板为唯一目的。
- 建议减少大规模模拟类题目的数量。

## 题目包要求

出题人需将与题目相关的所有文件打包为题目包，题目包应包含如下内容（假设题目名为 example）：

```sh
example.zip
├── std.cpp
├── gen.cpp
├── example.md
└── test.zip
    ├── 1.in
    ├── 1.out
    ├── 2.in
    ├── 2.out
    ├── ...
    └── [checker.cc]
```

其中：

- `*.md` 为该题目的题面说明。
- `std.cpp` 为该题目的标准程序。
- `gen.cpp` 为该题目的样例生成器，我们推荐使用 `testlib` ，可以保证在不同平台上同一个种子生成的随机数相同，并且种子会依据命令行参数自动生成。
- `*.in` 为该题目对应测试用例的标准输入。
- `*.out` 为该题目对应测试用例的标准输出。

可以参考[题目包示例]()

### 题面

题目包中提供的题面文件需要按照下方格式

```md
# example

## 题目描述
<!-- 这里填写题目描述 -->
## 输入描述
<!-- 这里填写输入描述 -->
## 输出描述
<!-- 这里填写输出描述 -->
## 测试样例
[示例1 输入 输出 说明(可选)]
[示例2 输入 输出 说明(可选)]
```

内容需要严格遵守[牛客系列赛命题规范](https://blog.nowcoder.net/n/6cb53e0afdff48ed8fbc046a077f6649)。
题目描述一定一定一定要清晰易懂，存在歧义的部分须单独说明。

### 随机样例

推荐出题人使用 `Testlib` 库，或者使用 `mt19937` 随机数生成器配合高精度时钟(std::chrono)生成随机数。
出题人需要保证测试用例中随机数据的均匀度。(比如使用rand() * rand()无法生成均匀分布的数据)
数据中应包含各个参数的最大值和最小值。
数据中应包含各种边角情况。
数据中应包含各种各样的构造。

gen.cpp示例：

```cpp
#include "testlib.h"

using namespace std;

int n, m, k;
vector<int> p;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int i;

  n = atoi(argv[1]);
  m = atoi(argv[2]);
  k = rnd.next(1, n);

  for (i = 1; i <= n; ++i) p.push_back(i);

  shuffle(p.begin(), p.end());
  // 使用 rnd.next() 进行 shuffle

  printf("%d %d %d\n", n, m, k);
  for (i = 0; i < n; ++i) {
    printf("%d%c", p[i], " \n"[i == n - 1]);
    // 把字符串当作数组用，中间空格，末尾换行，是一个造数据时常用的技巧
  }

  return 0;
}
```

### Special Judge

参考[牛客平台编写spj](https://www.nowcoder.com/discuss/353154397968474112)，这里不作展开。

官方文档中没有说明的漏洞：用户可能有多余输出，需自行判别。

### 标程规范

严格遵守[牛客系列赛命题规范](https://blog.nowcoder.net/n/6cb53e0afdff48ed8fbc046a077f6649)中的标程规范。

## 其他规范

- 出题人须在题目明确公开之前严格保密，如使用在公开比赛则被视作为公开，内部训练赛、验题场等场合使用不被视作公开。
- 验题人须严格遵守出题规范且需要按照该规范去审核题目。
- 验题人在验题后不论该题是否被采纳，均需在题目明确公开之前严格保密，公开标准见上文。
