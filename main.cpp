// Single Layer PLA
#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
#include <time.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"

double dot(std::vector<double> vec_1, std::vector<double> vec_2){
    int result=0;
    try {
        if(vec_1.size()!=vec_2.size()) throw "Two vector size aren't same.";
    } catch(const char* message) {
        std::cerr<<RED<<message<<RESET<<std::endl;
    }
    for(size_t i=0;i<vec_1.size();i++) result+=vec_1[i]*vec_2[i];
    return result;
}

std::string vec_to_str(std::vector<double> vec){
    std::string result;
    result+="{";
    for(size_t i=0;i<vec.size();i++) {
        result+=std::to_string(vec[i]);
        if(i==vec.size()-1) continue;
        result+=", ";
    }
    result+="}";

    return result;
}

class train_data{
    private:
        std::vector<double> inputs;
        int is_type;
    public:
        train_data(std::vector<double> inputs, int is_type);
        std::vector<double> get_intputs();
        int get_type();
        std::string to_str();

};

train_data::train_data(std::vector<double> inputs, int is_type){
    this->inputs=inputs;
    this->is_type=is_type;
}

std::vector<double> train_data::get_intputs(){
    return this->inputs;
}

int train_data::get_type(){
    return is_type;
}

std::string train_data::to_str(){
    std::string output;
    output+="train_data(";
    output+=vec_to_str(get_intputs());
    output+=", ";
    if(get_type()==1){
        output+=BLUE;
        output+="o";
        output+=RESET;
    }else{
        output+=RED;
        output+="x";
        output+=RESET;
    }
    output+=" )";

    return output;
}

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
        int activative_function(double x);

    public:
        void init();
        perceptron(std::vector<train_data> data, double learning_rate);
        double predict_type(train_data data);
        void train(int epochs,int reset);
        std::string to_str();

};

// private
void perceptron::init_weights(){
    weights={};
    size_t n_weights=data[0].get_intputs().size();
    for(size_t i=0;i<n_weights;i++) weights.push_back(1.000000);
}

void perceptron::init_bias(){
    this->bias=0;
}

double perceptron::cost(train_data data){
    int predict=predict_type(data);
    int actual=data.get_type();
    return learning_rate*(actual-predict);
}

void perceptron::update(train_data data){
    std::vector<double> intputs=data.get_intputs();
    double data_cost=cost(data);
    for(size_t i=0;i<intputs.size();i++){
        weights[i]+=intputs[i]*data_cost;
    }
}

void perceptron::train_epoch(){
    for(size_t i=0;i<data.size();i++){
        update(data[i]);
    }
}

int perceptron::activative_function(double x){
    return (x>0)?1:-1;
}

// public

void perceptron::init(){
    init_weights();
    init_bias();
}

std::string perceptron::to_str(){
    std::string output;
    output+="perceptron( weights: ";
    output+=vec_to_str(this->weights);
    output+=", bias: ";
    output+=std::to_string(this->bias);
    output+=", learning rate: ";
    output+=std::to_string(this->learning_rate);
    output+=" )";

    return output;
}

perceptron::perceptron(std::vector<train_data> data, double learning_rate){
    this->data=data;
    this->learning_rate=learning_rate;
    init();
}

double perceptron::predict_type(train_data data){
    std::vector<double> intputs=data.get_intputs();
    double x=dot(weights, intputs)+bias;
    return activative_function(x);
}

void perceptron::train(int epochs,int reset){
    if(reset) init();
    for(size_t i=0;i<epochs;i++){
        train_epoch();
        std::cout<<"[epoch: "<<i<<"] "<<to_str()<<std::endl;
    }
}

train_data intput_data(int dimension){
    std::vector<double> data;
    
    for(size_t i=0;i<dimension;i++){
        double temp_x;
        std::cout<<"X_"<<i<<": ";

        std::cin>>temp_x;
        data.push_back(temp_x);
    }

    int type;
    std::cout<<"type: ";
    std::cin>>type;
    try {
        if(type!=1||type!=-1) throw "Type is only accept 1 and -1.";
    } catch(const char* message) {
        std::cerr<<RED<<message<<RESET<<std::endl;
    }

    return train_data(data, type);
}

train_data _data(int i){
    int n_set=20;
    double set_[n_set][3]={ {2.5,   2.25,  -1},
                            {1,     1.5,   -1},
                            {2.5,   1.25,  -1},
                            {2,     0.5,   -1},
                            {1,     0,     -1},
                            {0.5,   -0.75, -1},
                            {2.75,  -0.75, -1},
                            {1.5,   -1.25, -1},
                            {0.25,  -1.75, -1},
                            {2,     -2.25, -1},
                            {0,     3,     1},
                            {-2.5,  2.5,   1},
                            {-2,    2,     1},
                            {-2.25, 1.25,  1},
                            {-1,    1,     1},
                            {-3,    0.25,  1},
                            {-1.25, 0.25,  1},
                            {-2.5,  -0.5,  1},
                            {-1.75, -1,    1},
                            {-2.75, -1.75, 1}};
    double x_1=set_[i][0];
    double x_2=set_[i][1];
    int type=set_[i][2];
    std::vector<double> temp_vec;
    temp_vec.push_back(x_1);
    temp_vec.push_back(x_2);

    std::cout<<train_data(temp_vec,type).to_str()<<"\n";
    return train_data(temp_vec,type);
}

int main(){
    std::vector<train_data> data;
    int n_data=20;
    double learning_rate=0;
    double n_correct=0;
    int n_epoch=0;
    clock_t start,end;

    for(size_t i=0;i<n_data;i++){
        data.push_back(_data(i));
    }

    std::cout<<"learning rate: ";
    std::cin>>learning_rate;
    std::cout<<"epoch: ";
    std::cin>>n_epoch;

    perceptron PLA(data, learning_rate);
    start = clock();
    PLA.train(n_epoch,false);
    end = clock();

    for(size_t i=0;i<n_data;i++){
        std::cout<<"data["<<i<<"]: predict -> "<<
        PLA.predict_type(data[i])<<", actual -> "<<data[i].to_str();
        if(PLA.predict_type(data[i])==data[i].get_type()){
            std::cout<<GREEN<<" ✓ \n"<<RESET;
            n_correct+=1;
        }else{
            std::cout<<RED<<" x \n"<<RESET;
        }
    }
    std::cout<<PLA.to_str()<<"\n";
    std::cout<<"correct rate: "<<(n_correct/n_data)*100<<"%, time: "<<((double)end-start)/CLK_TCK;
    
    return 0;
}