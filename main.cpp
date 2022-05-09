// Single Layer PLA
#include <iostream>
#include <vector> 
#include <string>
#include <algorithm>
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
    //std::cout<<result<<std::endl;
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
        bool is_type;
    public:
        train_data(std::vector<double> inputs, bool is_type);
        std::vector<double> get_intputs();
        bool get_type();
        std::string to_str();

};

train_data::train_data(std::vector<double> inputs, bool is_type){
    this->inputs=inputs;
    this->is_type=is_type;
}

std::vector<double> train_data::get_intputs(){
    return this->inputs;
}

bool train_data::get_type(){
    return is_type;
}

std::string train_data::to_str(){
    std::string output;
    output+="train_data(";
    output+=vec_to_str(get_intputs());
    output+=", ";
    if(get_type()){
        output+=BLUE;
        output+="o";
        output+=RESET;
    }else{
        output+=RED;
        output+="x";
        output+=RESET;
    }
    output+=")";

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

    public:
        perceptron(std::vector<train_data> data, double learning_rate);
        bool predict_type(train_data data);
        void train(int epochs,bool reset);
        std::string to_str();

};

void perceptron::init_weights(){
    std::cout<<"initializing weights...\n"; 
    weights={};
    size_t n_weights=data[0].get_intputs().size();
    for(size_t i=0;i<n_weights;i++) weights.push_back(1.000000);
    std::cout<<"weights: "<<vec_to_str(weights)<<"\n";
}

void perceptron::init_bias(){
    this->bias=0;
}

double perceptron::cost(train_data data){
    bool predict=predict_type(data);
    bool actual=data.get_type();
    return learning_rate*(actual-predict);
}

void perceptron::update(train_data data){
    //std::cout<<"updating...\n";
    std::vector<double> intputs=data.get_intputs();
    double data_cost=cost(data);
    //std::cout<<"cost: "<<data_cost<<"\n";
    for(size_t i=0;i<intputs.size();i++){
        weights[i]+=intputs[i]*data_cost;
        //std::cout<<"["<<i<<"] -> "<<weights[i]<<"\n";
    }
    //std::cout<<vec_to_str(weights)<<"\n";
}

void perceptron::train_epoch(){
    for(size_t i=0;i<data.size();i++){
        //std::cout<<"[Data "<<i<<"] training...\n"; 
        update(data[i]);
    }
}

std::string perceptron::to_str(){
    std::string output;
    output+="perceptron(weights: ";
    output+=vec_to_str(this->weights);
    output+=", bias: ";
    output+=std::to_string(this->bias);
    output+=", learning rate: ";
    output+=std::to_string(this->learning_rate);

    return output;
}

perceptron::perceptron(std::vector<train_data> data, double learning_rate){
    this->data=data;
    this->learning_rate=learning_rate;
    init_weights();
    init_bias();
}

bool perceptron::predict_type(train_data data){
    std::vector<double> intputs=data.get_intputs();
    return dot(weights, intputs)+bias > 0;
}

void perceptron::train(int epochs,bool reset){
    //std::cout<<"training...\n";
    if(reset){
        init_weights();
        init_bias();
    }
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
    //std::cout<<vec_to_str(data)<<" "<<data.size();

    bool type;
    std::cout<<"type: ";
    std::cin>>type;
    try {
        if(type>1||type<0) throw "Type is only accept true and false.";
    } catch(const char* message) {
        std::cerr<<RED<<message<<RESET<<std::endl;
    }

    return train_data(data, type);
}

int main(){
    std::vector<train_data> data;
    int n_data=0;
    int n_dimension=0;
    double learning_rate=0;
    std::cout<<"dimension: ";
    std::cin>>n_dimension;
    std::cout<<"data amount: ";
    std::cin>>n_data;

    for(size_t i=0;i<n_data;i++){
        std::cout<<"[Data_"<<i<<"]\n";
        data.push_back(intput_data(n_dimension));
    }

    for(int i=0;i<data.size();i++){
        std::cout<<data[i].to_str()<<"\n";
    }

    std::cout<<"learning rate: ";
    std::cin>>learning_rate;

    perceptron PLA(data, learning_rate);
    PLA.train(20,false);
    std::cout<<PLA.to_str()<<"\n";
    for(size_t i=0;i<n_data;i++){
        std::cout<<"data["<<i<<"]: predict -> "<<
        PLA.predict_type(data[i])<<", actual -> "<<data[i].to_str();
        if(PLA.predict_type(data[i])==data[i].get_type()) std::cout<<GREEN<<" ✓\n"<<RESET;
        else std::cout<<RED<<" x\n"<<RESET;
    }
    
    return 0;
}