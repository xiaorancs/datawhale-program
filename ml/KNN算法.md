## 算法原理

KNN 算法采用测量不同特征之间的距离方法进行分类，通俗的讲就是：给定一个样本数据集，并且样本集中每个数据都存在标签，即我们知道样本集中每个数据与所属分类的对应关系。对新输入没有标签的实例，在训练数据集中找到与该实例最邻近的 k 个实例，这 k 个实例的多数属于某个类，就把该输入实例分为这个类。

```
对于每一个在数据集中的数据点：
    计算目标的数据点（需要分类的数据点）与该数据点的距离
    将距离排序：从小到大
    选取前 K 个最短距离
    选取这 K 个中最多的分类类别
    返回该类别来作为目标数据点的预测值
```


---
## 项目案例1：优化约会网站的配对效果


<b>项目概述</b>

海伦使用约会网站寻找约会对象。经过一段时间之后，她发现曾交往过三种类型的人:

- 1：不喜欢的人
- 2：魅力一般的人
- 3：极具魅力的人


她希望：

- 不喜欢的人则直接排除掉
- 工作日与魅力一般的人约会
- 周末与极具魅力的人约会


现在她收集到了一些约会网站未曾记录的数据信息，这更有助于匹配对象的归类。

<b>开发流程</b>

<u>Step1：收集数据</u>

此案例书中提供了文本文件。

海伦把这些约会对象的数据存放在文本文件 datingTestSet2.txt 中，总共有 1000 行。海伦约会的对象主要包含以下 3 种特征：

- `Col1`：每年获得的飞行常客里程数 
- `Col2`：玩视频游戏所耗时间百分比 
- `Col3`：每周消费的冰淇淋公升数 

文本文件数据格式如下：
```python
40920	8.326976	0.953952	3
14488	7.153469	1.673904	2
26052	1.441871	0.805124	1
75136	13.147394	0.428964	1
38344	1.669788	0.134296	1
```

<u>Step2：准备数据</u>

使用 Python 解析文本文件。将文本记录转换为 NumPy 的解析程序如下所示：

```python
import numpy as np

def file2matrix(filename):
    """
    Desc:
        导入训练数据
    parameters:
        filename: 数据文件路径
    return:
        数据矩阵 returnMat 和对应的类别 classLabelVector
    """
    fr = open(filename)
    # 获得文件中的数据行的行数
    lines = fr.readlines()
    numberOfLines = len(lines)  # type: int
    # 生成对应的空矩阵
    # 例如：zeros(2，3)就是生成一个 2*3的矩阵，各个位置上全是 0
    returnMat = np.zeros((numberOfLines, 3))  # prepare matrix to return
    classLabelVector = []  # prepare labels return
    index = 0
    for line in lines:
        # str.strip([chars]) --返回已移除字符串头尾指定字符所生成的新字符串
        line = line.strip()
        # 以 '\t' 切割字符串
        listFromLine = line.split('\t')
        # 每列的属性数据
        returnMat[index, :] = listFromLine[0:3]
        # 每列的类别数据，就是 label 标签数据
        classLabelVector.append(int(listFromLine[-1]))
        index += 1
    # 返回数据矩阵returnMat和对应的类别classLabelVector
    return returnMat, classLabelVector
```

<u>Step3：分析数据</u>

使用 Matplotlib 画二维散点图。

```python
import matplotlib.pyplot as plt

if __name__ == '__main__':
    datingDataMat, datingLabels = file2matrix('datingTestSet2.txt')
    color = ['r', 'g', 'b']
    fig = plt.figure()
    ax = fig.add_subplot(311)
    for i in range(1, 4):
        index = np.where(np.array(datingLabels) == i)
        ax.scatter(datingDataMat[index, 0], datingDataMat[index, 1], c=color[i - 1], label=i)
    plt.xlabel('Col.0')
    plt.ylabel('Col.1')
    plt.legend()
    bx = fig.add_subplot(312)
    for i in range(1, 4):
        index = np.where(np.array(datingLabels) == i)
        bx.scatter(datingDataMat[index, 0], datingDataMat[index, 2], c=color[i - 1], label=i)
    plt.xlabel('Col.0')
    plt.ylabel('Col.2')
    plt.legend()
    cx = fig.add_subplot(313)
    for i in range(1, 4):
        index = np.where(np.array(datingLabels) == i)
        cx.scatter(datingDataMat[index, 1], datingDataMat[index, 2], c=color[i - 1], label=i)
    plt.xlabel('Col.1')
    plt.ylabel('Col.2')
    plt.legend()
    plt.show()
```

图中清晰地标识了三个不同的样本分类区域，具有不同爱好的人其类别区域也不同。

![](https://img-blog.csdnimg.cn/20191113165917996.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0xTR09fTVlQ,size_16,color_FFFFFF,t_70)



归一化特征值，消除特征之间量级不同导致的影响。

```python
def autoNorm(dataSet):
    """
    Desc:
        归一化特征值，消除特征之间量级不同导致的影响
    parameter:
        dataSet: 数据集
    return:
        归一化后的数据集 normDataSet.ranges和minVals即最小值与范围，并没有用到

    归一化公式：
        Y = (X-Xmin)/(Xmax-Xmin)
        其中的 min 和 max 分别是数据集中的最小特征值和最大特征值。该函数可以自动将数字特征值转化为0到1的区间。
    """
    # 计算每种属性的最大值、最小值、范围
    minVals = np.min(dataSet, axis=0)
    maxVals = np.max(dataSet, axis=0)
    # 极差
    ranges = maxVals - minVals
    m = dataSet.shape[0]
    # 生成与最小值之差组成的矩阵
    normDataSet = dataSet - np.tile(minVals, (m, 1))
    # 将最小值之差除以范围组成矩阵
    normDataSet = normDataSet / np.tile(ranges, (m, 1))  # element wise divide
    return normDataSet, ranges, minVals
```


<u>Step4：训练算法</u>

此步骤不适用于 k-近邻算法。因为测试数据每一次都要与全部的训练数据进行比较，所以这个过程是没有必要的。

```python
import operator

def classify0(inX, dataSet, labels, k):
    dataSetSize = dataSet.shape[0]
    # 距离度量 度量公式为欧氏距离
    diffMat = np.tile(inX, (dataSetSize, 1)) - dataSet
    sqDiffMat = diffMat ** 2
    sqDistances = np.sum(sqDiffMat, axis=1)
    distances = sqDistances ** 0.5
    # 将距离排序：从小到大
    sortedDistIndicies = distances.argsort()
    # 选取前K个最短距离， 选取这K个中最多的分类类别
    classCount = {}
    for i in range(k):
        voteIlabel = labels[sortedDistIndicies[i]]
        classCount[voteIlabel] = classCount.get(voteIlabel, 0) + 1
    sortedClassCount = sorted(classCount.items(), key=operator.itemgetter(1), reverse=True)
    return sortedClassCount[0][0]
```

<u>Step5：测试算法</u>

计算错误率，使用海伦提供的部分数据作为测试样本。如果预测分类与实际类别不同，则标记为一个错误。

```python
def datingClassTest():
    """
    Desc:
        对约会网站的测试方法
    parameters:
        none
    return:
        错误数
    """
    # 设置测试数据的的一个比例
    hoRatio = 0.1  # 测试范围,一部分测试一部分作为样本
    # 从文件中加载数据
    datingDataMat, datingLabels = file2matrix('datingTestSet2.txt')  # load data setfrom file
    # 归一化数据
    normMat, ranges, minVals = autoNorm(datingDataMat)
    # m 表示数据的行数，即矩阵的第一维
    m = normMat.shape[0]
    # 设置测试的样本数量， numTestVecs:m表示训练样本的数量
    numTestVecs = int(m * hoRatio)
    print('numTestVecs=', numTestVecs)
    errorCount = 0.0
    for i in range(numTestVecs):
        # 对数据测试
        classifierResult = classify0(normMat[i, :], normMat[numTestVecs:m, :], datingLabels[numTestVecs:m], 3)
        print("分类器返回结果: %d, 实际结果: %d" % (classifierResult, datingLabels[i]))
        if classifierResult != datingLabels[i]:
            errorCount += 1.0
    print("错误率: %f" % (errorCount / float(numTestVecs)))
    print(errorCount)
```

<u>Step6：使用算法</u>

产生简单的命令行程序，然后海伦可以输入一些特征数据以判断对方是否为自己喜欢的类型。

约会网站预测函数如下：

```python
def classifyPerson():
    resultList = ['不喜欢的人', '魅力一般的人', '极具魅力的人']
    ffMiles = float(input("每年获得的飞行常客里程数?"))
    percentTats = float(input("玩视频游戏所耗时间百分比?"))
    iceCream = float(input("每周消费的冰淇淋公升数?"))
    datingDataMat, datingLabels = file2matrix('datingTestSet2.txt')
    normMat, ranges, minVals = autoNorm(datingDataMat)
    inArr = np.array([ffMiles, percentTats, iceCream])
    intX = (inArr - minVals) / ranges
    classifierResult = classify0(intX, normMat, datingLabels, 3)
    print("这个人属于: ", resultList[classifierResult - 1])
```

实际运行效果如下:

```python
if __name__ == '__main__':
    classifyPerson()

'''
每年获得的飞行常客里程数? 10000
玩视频游戏所耗时间百分比? 10
每周消费的冰淇淋公升数? 0.5
这个人属于:  魅力一般的人
'''
```


---
## 项目案例2：手写识别系统

<b>项目概述</b>

构造一个能识别数字 0 到 9 的基于 KNN 分类器的手写数字识别系统。

需要识别的数字是存储在文本文件中的具有相同的色彩和大小：宽高是 32 像素 * 32 像素的黑白图像。

<b>开发流程</b>

<u>Step1：收集数据</u>

本案例书中提供了文本文件。

目录 trainingDigits 中包含了大约 2000 个例子，每个例子内容如下图所示，每个数字大约有 200 个样本；目录 testDigits 中包含了大约 900 个测试数据。

![](https://img-blog.csdnimg.cn/20191113143511395.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L0xTR09fTVlQ,size_16,color_FFFFFF,t_70)

<u>Step2：准备数据</u>

编写函数 `img2vector()`， 将图像文本数据转换为分类器使用的向量。

```python
def img2vector(filename):
    returnVect = np.zeros((1, 1024))
    fr = open(filename)
    for i in range(32):  # 32行
        lineStr = fr.readline()
        for j in range(32):  # 32列
            returnVect[0, 32 * i + j] = int(lineStr[j])
    return returnVect
```

<u>Step3：分析数据</u>

在 Python 命令提示符中检查数据，确保它符合要求。

```python
testVector = img2vector(r'./digits/trainingDigits/0_13.txt')
print(testVector[0, 0:32])
# [ 0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  1.  1.  1.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.]
print(testVector[0, 32:64])
# [ 0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  1.  1.  1.  1.  1.  1.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.  0.]
```

<u>Step4：训练算法</u>

此步骤不适用于 k-近邻算法。因为测试数据每一次都要与全部的训练数据进行比较，所以这个过程是没有必要的。

<u>Step5：测试算法</u>

计算错误率，编写函数使用提供的部分数据集作为测试样本，如果预测分类与实际类别不同，则标记为一个错误。

```python
import os

def handwritingClassTest():
    # 1. 导入训练数据
    hwLabels = []
    trainingFileList = os.listdir(r'./digits/trainingDigits')  # load the training set
    m = len(trainingFileList)
    trainingMat = np.zeros((m, 1024))
    # hwLabels存储0～9对应的index位置， trainingMat存放的每个位置对应的图片向量
    for i in range(m):
        fileNameStr = trainingFileList[i]
        fileStr = fileNameStr.split('.')[0]  # take off .txt
        classNumStr = int(fileStr.split('_')[0])
        hwLabels.append(classNumStr)
        # 将 32*32的矩阵->1*1024的矩阵
        trainingMat[i, :] = img2vector(r'./digits/trainingDigits/%s' % fileNameStr)

    # 2. 导入测试数据
    testFileList = os.listdir(r'./digits/testDigits')  # iterate through the test set
    errorCount = 0.0
    mTest = len(testFileList)
    for i in range(mTest):
        fileNameStr = testFileList[i]
        fileStr = fileNameStr.split('.')[0]  # take off .txt
        classNumStr = int(fileStr.split('_')[0])
        vectorUnderTest = img2vector(r'./digits/testDigits/%s' % fileNameStr)
        classifierResult = classify0(vectorUnderTest, trainingMat, hwLabels, 3)
        print("分类器返回结果: %d, 实际结果: %d" % (classifierResult, classNumStr))
        if classifierResult != classNumStr:
            errorCount += 1.0
    print("分类错误数量: %d" % errorCount)
    print("分类错误率: %f" % (errorCount / float(mTest)))
```

<u>Step6：使用算法</u>

可以构造一个小的软件系统，从图像中提取数字，并完成数字识别，我们现实中使用的OCR，以及车牌识别都类似于这样的系统。
