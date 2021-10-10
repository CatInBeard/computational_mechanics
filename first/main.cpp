#include<main.h>
// u(x,0)=sin(x)+0.08
// u(0,t)=0.08+2t
// u(0.6,t)=0.6446
// t = [0;0.01]
// x = [0;0.6]
// Ro=1
// Cv=1
// Lambda =1

const int N_t=5;
const int N_x=7;

const double Ro=1;
const double Cv=1;
const double Lambda =1;

const double t_max=0.01;

const double h=0.1;
const double dt=t_max/(N_t-1);

double u_x(double x){
    return sin(x)+0.08;
}
double u_t_left(double t){
    return 0.08+2*t;
}
double u_t_right(double t){
    return 0.6446;
}
void write_xyz(std::string file,double T[N_x][N_t]){
    std::ofstream out;
    out.open(file);
    if (out.is_open()){
        out <<"x t T"<<std::endl;
        for(int i=0;i<N_x;i++){
            for(int j=0;j<N_t;j++){
                out <<i*h<<" "<<j*dt<<" "<< T[i][j]<<std::endl;
            }
        }
    }
    else{
        std::cout<<"Can't write into "<<file<<std::endl;
    }
}
void write_pre_latex(std::string file,double T[N_x][N_t]){
    std::ofstream out;
    out.open(file);
    if (out.is_open()){
        out <<"0";
        for(int i=0;i<N_x;i++){
            out <<","<<i*h;
        }
        out <<std::endl;
        for(int j=0;j<N_t;j++){
            out << j*dt;
            for(int i=0;i<N_x;i++){
                out <<","<<T[i][j];
            }
            out <<std::endl;
        }
    }
    else{
        std::cout<<"Can't write into "<<file<<std::endl;
    }
}
void write_xz(std::string file,int N,double T[N_x][N_t]){
    std::ofstream out;
    out.open(file);
    if(out.is_open()){
        out <<"x t="<<N*dt<<std::endl;
        for(int i=0;i<N_x;i++){
            out <<i*h<<" "<< T[i][N]<<std::endl;
        }
    }
    else{
        std::cout<<"Can't write into "<<file<<std::endl;
    }
}

void get_T(double (&T)[N_x][N_t]){
    for(int i=0;i<N_x;i++){
        for(int j=0;j<N_t;j++){
            T[i][j]=0;
        }
    }

    for(int i=0;i<N_x;i++){
        T[i][0]=u_x(i*h);
    }
    for(int i=0;i<N_t;i++){
        T[0][i]=u_t_left(i*dt);
        T[N_x-1][i]=u_t_right(i*dt);
    }
}
void explicit_schema(){
    double T[N_x][N_t];
    get_T(T);

    for(int i=0;i<N_t-1;i++){
        for(int j=1;j<N_x-1;j++){
            T[j][i+1]=dt*Lambda/(Ro*h*h*Cv)*(T[j+1][i]-2*T[j][i]+T[j-1][i])+T[j][i];
        }    
    }
    write_xyz("data/data1_xyz.csv",T);
    write_pre_latex("data/data1_latex.csv",T);
    write_xz("data/data1_1_xz.csv",N_t-3,T);
    write_xz("data/data1_2_xz.csv",N_t-2,T);
    write_xz("data/data1_3_xz.csv",N_t-1,T);
}
void implicit_schema(){
    double T[N_x][N_t];
    get_T(T);

    const double A=Lambda/(h*h);
    const double C=A;
    const double B=(Ro*Cv*h*h+2*Lambda*dt)/(dt*h*h);
    for(int i=0;i<N_t-1;i++){
        double F[N_x];
        for(int j=0;j<N_x;j++){
            F[j]=Ro*Cv/dt*T[j][i];
        }
        double S[N_x];
        double M[N_x];
        S[0]=C/B;
        M[0]=F[0]/B;
        for(int j=1;j<N_x;j++){
            S[j]=C/(-A*S[j-1]+B);
            M[j]=(F[j]+A*M[j-1])/(B-A*S[j-1]);
        }
        for(int j=N_x-1;j>=0;j--){
            T[j][i+1]=S[j]*T[j+1][i+1]+M[j];
        }
    }
    for(int i=0;i<N_t;i++){
        T[N_x-1][i]=u_t_right(i*dt);
    }
    write_xyz("data/data2_xyz.csv",T);
    write_pre_latex("data/data2_latex.csv",T);
    write_xz("data/data2_1_xz.csv",N_t-3,T);
    write_xz("data/data2_2_xz.csv",N_t-2,T);
    write_xz("data/data2_3_xz.csv",N_t-1,T);
}
int main(){
    explicit_schema();
    implicit_schema();
    return 0;
}