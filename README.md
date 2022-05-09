# 函式&變數
+ `dot()`，將兩向量(double)內積並回傳其值(double)。
```cpp
double dot(std::vector<double> vec_1, std::vector<double> vec_2);
```
+ `vec_to_str()`，將向量轉換成 `string` 並回傳。
```cpp
std::string vec_to_str(std::vector<double> vec);
```
+ `intput_data()`，輸入一組資料(輸入向量&類型)
```cpp
train_data intput_data(int dimension);
```

## class train_data
```cpp
class train_data{
    private:
        std::vector<double> inputs;
        bool is_type;
    public:
        train_data(std::vector<double> inputs, bool is_type);
        std::vector<double> get_intputs();
        bool get_type();
        std::string to_str();

};
```

### private
+ 輸入層向量。
```cpp
std::vector<double> inputs;
```
+ 類型。
```cpp
bool is_type;
```

### public
+ 建構元，直接初始化輸入向量和類型。
```cpp
train_data(std::vector<double> inputs, bool is_type);
```
+ `get_intputs()`，回傳輸入層向量。
```cpp
std::vector<double> get_intputs();
```
+ `get_type()`，回傳類型。
```cpp
bool get_type();
```
+ `to_str()`，將 `train_data` 物件的輸入向量、類型轉換成字串回傳。
```cpp
std::string to_str();
```

## class perceptron
```cpp
class perceptron{
    private:
        std::vector<train_data> data;
        std::vector<double> weights;
        double bias;
        double learning_rate; 
        void init_weights();
        void init_bias();
        double cost(train_data data);
        void update(train_data data);
        void train_epoch();

    public:
        perceptron(std::vector<train_data> data, double learning_rate);
        bool predict_type(train_data data);
        void train(int epochs,bool reset);
        std::string to_str();

};
```

### private
+ `data`，訓練資料陣列。
```cpp
std::vector<train_data> data;
```
+ `weights`，權重向量。
```cpp
std::vector<double> weights;
```
+ `bias`，偏置值(閥值)。
```cpp
double bias;
```
+ `learning_rate`，學習率。
```cpp
double learning_rate;
```
+ `init_weights()`，初始化權重向量。
```cpp
void init_weights();
```
+ `init_bias`，初始化偏置值。
```cpp
void init_bias();
```
+ `cost()`，回傳 cost
```cpp
double cost(train_data data);
```
+ `update()`，更新權重。
```cpp
void update(train_data data);
```
+ train_epoch()，訓練完一組資料。
```cpp
void train_epoch();
```

### public
+ 建構元，設定輸入向量陣列、學習率。
```cpp
perceptron(std::vector<train_data> data, double learning_rate);
```
+ `predict_type()`，感知姬預測的類型
```cpp
bool predict_type(train_data data);
```
+ `train()`，訓練感知機。
```cpp
void train(int epochs,bool reset);
```
+ `to_str()`，把權重、偏置值及學習率轉換成字串後回傳。
```cpp
std::string to_str();
```