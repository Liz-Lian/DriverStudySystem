此项目为本人学校课设作业，粗制滥造，仅供参考与学习。
---
# DriverStudySystem - 驾驶员理论课程模拟考试与学习系统

这是一个基于 Qt 6 (C++) 开发的驾驶员理论考试模拟系统。该项目采用了 MVC (Model-View-Controller) 架构模式，实现了用户登录、模拟考试、自由练习、错题回顾、成绩查询以及管理员题库管理等功能。

## 项目结构说明

项目文件按照 MVC 架构组织，主要分为以下几个部分：

### 1. 根目录 (Root)

- **`CMakeLists.txt`**: CMake 构建配置文件，定义了项目依赖 (Qt Widgets)、包含路径和源文件列表。
- **`main.cpp`**: 程序的入口点，负责初始化 `QApplication`，加载 QSS 样式表，并显示主窗口 (`MainWindow`)。
- **`questions.txt`**: 题库数据文件。存储了所有的考试题目信息（题目内容、选项、正确答案）。
- **`scores.txt`**: 成绩数据文件。存储了用户的考试历史记录（用户 ID、分数、时间、模式）。
- **`style.qss`**: 全局样式表文件。定义了应用程序的配色、控件样式（扁平化按钮、圆角、交互效果等）。
- **`resources.qrc`**: Qt 资源配置文件。将 `style.qss` 打包进应用程序中。

### 2. 模型层 (Models)

负责数据的定义、存储和管理。

- **`Models/GlobalTypes.h`**: 定义了全局通用的数据结构和枚举。
  - `struct Question`: 定义题目结构（ID, 内容, 选项 A-D, 答案）。
  - `struct ExamRecord`: 定义考试记录结构（用户 ID, 分数, 时间, 模式）。
  - `enum ExamMode`: 定义考试模式（模拟考试, 自由训练）。
- **`Models/QuestionManager.h` / `.cpp`**: 题库管理类。
  - 负责从 `questions.txt` 加载题目。
  - 提供获取所有题目、添加题目、更新题目、删除题目的接口。
  - 负责将修改后的题库保存回文件。
- **`Models/ScoreManager.h` / `.cpp`**: 成绩管理类。
  - 负责从 `scores.txt` 加载成绩记录。
  - 提供保存新成绩、查询特定用户成绩的接口。

### 3. 控制层 (Controllers)

负责业务逻辑的处理，连接 View 和 Model。

- **`Controllers/ExamController.h` / `.cpp`**: 考试逻辑控制器。
  - 管理考试流程（开始、停止）。
  - 管理考试计时器 (`QTimer`)。
  - 处理考试模式（模拟考试 vs 自由训练）的逻辑差异（如随机抽题 vs 顺序练习）。
- **`Controllers/AdminController.h` / `.cpp`**: 管理员逻辑控制器。
  - 处理管理员界面的交互逻辑。
  - 实现题目的增删改查操作，并调用 `QuestionManager` 进行数据持久化。
  - 处理题目的搜索过滤功能。
- **`Controllers/ScoreController.h` / `.cpp`**: 成绩逻辑控制器。
  - 负责处理成绩查询界面的逻辑。
  - 调用 `ScoreManager` 获取数据并格式化，供 View 层显示。
- **`Controllers/ReviewController.h` / `.cpp`**: 错题回顾控制器。
  - 在考试结束后，负责比对用户答案和正确答案。
  - 筛选出用户做错的题目，供错题回顾界面使用。

### 4. 视图层 (Views)

负责用户界面的展示和交互。

- **`Views/mainwindow.ui`**: Qt Designer 设计的 UI 文件 (XML 格式)。定义了 `QStackedWidget` 多页面布局，包括登录页、菜单页、考试页、管理页、成绩页和错题回顾页。
- **`Views/mainwindow.h`**: 主窗口类的头文件，定义了所有成员变量和槽函数。
- **`Views/mainwindow.cpp`**: 主窗口核心逻辑。
  - 负责初始化 UI 和各个 Controller/Manager。
  - 处理登录、页面跳转、管理员和成绩管理的基础交互。
- **`Views/MainWindow_Exam.cpp`**: 考试相关 UI 逻辑。
  - 处理模拟考试和自由训练的模式选择。
  - 负责题目显示 (`showQuestion`)、下一题切换、交卷评分逻辑。
  - 处理倒计时更新。
- **`Views/MainWindow_Review.cpp`**: 错题回顾 UI 逻辑。
  - 负责错题的展示 (`showWrongQuestion`)。
  - 实现视觉反馈：将用户错选标红，正确答案标绿。
  - 处理错题回顾的导航（下一题、退出）。

## 功能概览

1.  **用户登录**: 输入用户 ID 进入系统。
2.  **管理员登录**: 特定账号密码进入后台管理。
3.  **模拟考试**: 随机抽取题目，限时考试，考完自动评分。
4.  **自由训练**: 顺序练习所有题目，无时间限制。
5.  **错题回顾**: 考试结束后，可查看本次考试的错题，系统会高亮显示用户错选项（红色）和正确选项（绿色）。
6.  **成绩查询**: 查看历史考试成绩。
7.  **题库管理**: 管理员可以添加、修改、删除和搜索题目。支持多行文本输入和占位符提示。
8.  **现代化 UI**: 采用扁平化设计风格，优化了按钮交互和视觉体验。

## 编译环境

- **OS**: Windows
- **Compiler**: MinGW 64-bit
- **Framework**: Qt 6.8.2
- **Build System**: CMake
