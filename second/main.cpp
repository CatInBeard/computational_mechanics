#include <main.h>

//u(x,0)=f(x)=x*(2*x-0.5)
//ut(x,0)=F(x)=cos(2*x)
//0<=x<=1
//u(0,t)=phi(t)=t*t
//u(1,t)=psi(t)=1.5
//h=0.1
//0<=t<=0.25

const int N_t=11;
const int N_x=11;

const double C=1;
const double t_max=0.5;

const double h=0.1;
const double dt=t_max/(N_t-1);

double u_x(double x){
    return x*(2*x-0.5);
}
double u_t_x(double x){
    return cos(2*x);
}
double u_t_left(double t){
    return t*t;
}
double u_t_right(double t){
    return 1.5;
}
void write_xyz(std::string file,double U[N_x][N_t]){
    std::ofstream out;
    out.open(file);
    if (out.is_open()){
        out <<"x t U"<<std::endl;
        for(int i=0;i<N_x;i++){
            for(int j=0;j<N_t;j++){
                out <<i*h<<" "<<j*dt<<" "<< U[i][j]<<std::endl;
            }
        }
    }
    else{
        std::cout<<"Can't write into "<<file<<std::endl;
    }
}
void write_pre_latex(std::string file,double U[N_x][N_t]){
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
                out <<","<<U[i][j];
            }
            out <<std::endl;
        }
    }
    else{
        std::cout<<"Can't write into "<<file<<std::endl;
    }
}
void write_xz(std::string file,int N,double U[N_x][N_t]){
    std::ofstream out;
    out.open(file);
    if(out.is_open()){
        out <<"x t="<<N*dt<<std::endl;
        for(int i=0;i<N_x;i++){
            out <<i*h<<" "<< U[i][N]<<std::endl;
        }
    }
    else{
        std::cout<<"Can't write into "<<file<<std::endl;
    }
}

void get_U(double (&U)[N_x][N_t]){
    for(int i=0;i<N_x;i++){
        for(int j=0;j<N_t;j++){
            U[i][j]=0;
        }
    }
    for(int i=0;i<N_t;i++){
        U[0][i]=u_t_left(i*dt);
        U[N_x-1][i]=u_t_right(i*dt);
    }
    for(int i=0;i<N_x;i++){
        U[i][0]=u_x(i*h);
    }
    for(int i=1;i<N_x-1;i++){
        U[i][1]=U[i][0]+u_t_x(i*h)*dt+dt*dt/(2*h*h)*(U[i+1][0]-2*U[i][0]+U[i-1][0]);
    }
}
void explicit_schema(){
    double U[N_x][N_t];
    get_U(U);
    for(int i=1;i<N_t-1;i++){
        for(int j=1;j<N_x-1;j++){
            U[j][i+1]=(C*C)*(dt*dt)/(h*h)*(U[j-1][i]-2*U[j][i]+U[j+1][i])+2*U[j][i]-U[j][i-1];
        }    
    }
    write_xyz("data/data1_xyz.csv",U);
    write_pre_latex("data/data1_latex.csv",U);
    write_xz("data/data1_1_xz.csv",N_t-3,U);
    write_xz("data/data1_2_xz.csv",N_t-2,U);
    write_xz("data/data1_3_xz.csv",N_t-1,U);
}
void implicit_schema(){
    double U[N_x][N_t];
    get_U(U);
    const double A=1/(h*h);
    const double C=A;
    const double B=(h*h+2*dt*dt)/(dt*dt*h*h);
    for(int i=1;i<N_t-1;i++){
        double F[N_x];
        for(int j=0;j<N_x;j++){
            F[j]=(2*U[j][i]-U[j][i-1])*1/(dt*dt);
        }
        double S[N_x];
        double M[N_x];
        S[0]=C/B;
        M[0]=F[0]/B;
        for(int j=1;j<N_x;j++){
            S[j]=C/(B-A*S[j-1]);
            M[j]=(F[j]+A*M[j-1])/(B-A*S[j-1]);
        }
        for(int j=N_x-2;j>1;j--){
            U[j][i+1]=S[j]*U[j+1][i+1]+M[j];
        }
    }
    for(int i=0;i<N_t;i++){
        U[N_x-1][i]=u_t_right(i*dt);
    }
    write_xyz("data/data2_xyz.csv",U);
    write_pre_latex("data/data2_latex.csv",U);
    write_xz("data/data2_1_xz.csv",N_t-3,U);
    write_xz("data/data2_2_xz.csv",N_t-2,U);
    write_xz("data/data2_3_xz.csv",N_t-1,U);
}
int main(){
    explicit_schema();
    implicit_schema();
    return 0;
}