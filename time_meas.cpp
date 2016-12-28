/* Maarten Sprengers    2016-2017    WIT    r0256246
   uren gewerkt aan de taak: 8uur 30min
   compiler: c++ -O3 -std=c++14 -DNDEBUG time_meas.cpp
   machine durbuy
   total of 8 files
   files used: vector.hpp, matrix.hpp, is_vector.hpp, is_matrix.hpp,
   vector_expression_operations.hpp, matrix_expression_operations.hpp

* Voor- en nadelen van expressie templates
   + Er wordt geen geheugen extra gebruikt voor het uitrekenen van de
      gevraagde berekening.
   - Als er meerdere maal hetzelfde (tussenresultaat) opgevraagd wordt,
     wordt dit telkens berekend, dit kan zorgen voor een hogere complexiteit.
     -> dit is wat er gebeurt bij de berekening zonder temp variabele.

* Complexiteit met en zonder temp variabele
   * Zonder: - matrix*vector is van O(N^2)
             - vector*scalar is O(N) dit is verwaarloosbaar voor grote N
             - voor matrix*(matrix*vector) wordt O(n^2) N maal aangeroepen
               en wordt dit dus O(N^3)
   * Met: - wordt er 2 maalmatrix*vector gedaan, dit blijft O(N^2)
          - vector*scalar is O(N) dit is verwaarloosbaar voor grote N

   -> Op de grafiek is dit resultaat duidelijk waar te nemen. Op de x-as staat
      N, de grootte van de matrix (NxN) en vector (N). Op de y-as het gemiddelde
      van de tijdsmetingen voor die bepaalde N met en zonder een temp variabele. 
*/

#include "vector.hpp"
#include "matrix.hpp"
#include "matrix_expression_operations.hpp"
#include "vector_expression_operations.hpp"
#include <time.h>

int main() {

// performantie metingen
  int max_pow=11;
  int number_exp=25;
  int discard=5;
  struct timespec l_start, l_end;

  tws::matrix<double> t_m_1(max_pow,3,0.0);
  tws::matrix<double> t_m_2(max_pow,3,0.0);

for(int c=0;c<2;c++){

for(int n=0;n<max_pow;n++){
  double elapsed_time=0.;
  double average_time=0.;
  double squared_time=0.;
  double time_diff=0.;
  int N = int(pow(double(2),double(n))) ;
  double beta = 0.7616515;
  tws::vector<double> x(N,0.0);
  tws::vector<double> y(N,0.0);
  tws::vector<double> temp(N,0.0);
  x.randomize();
  tws::matrix<double> X(N,N,0.0);
  X.randomize();

  for(int exp=0;exp<number_exp+discard;exp++){
    if (c==0){
    clock_gettime(CLOCK_MONOTONIC, &l_start);
    y=multiply(transpose(X),multiply(X,x))+beta*x;
    clock_gettime(CLOCK_MONOTONIC, &l_end);
    } else if(c==1){
    clock_gettime(CLOCK_MONOTONIC, &l_start);
    temp=multiply(X,x);
    y=multiply(transpose(X),temp)+beta*x;
    clock_gettime(CLOCK_MONOTONIC, &l_end);
    }
    if(exp>=discard){
       elapsed_time=(l_end.tv_sec - l_start.tv_sec)+(l_end.tv_nsec - l_start.tv_nsec) / 1000000000.0;
       time_diff=elapsed_time-average_time;
       average_time+=time_diff/(exp-discard+1);
       squared_time+=time_diff*(elapsed_time-average_time);
    }
   }
if (c==0) {
 t_m_1(n,0)=double(N);
 t_m_1(n,1)=average_time;
 t_m_1(n,2)=(std::sqrt(squared_time/(number_exp-1)));
} else if (c==1){
 t_m_2(n,0)=double(N);
 t_m_2(n,1)=average_time;
 t_m_2(n,2)=(std::sqrt(squared_time/(number_exp-1)));
}
}
}
std::cout<<t_m_1;
std::cout<<t_m_2;

  return 0 ;
}
