/*
 * created by : Merve Unlu
 */

#ifndef STRUCTPOINT_H_
#define STRUCTPOINT_H_

/*
 * Point yapisi koordinat duzleminde 
 * bir noktayi ifade eder. 
 * iki tane elemani vardir: x, y
 */ 
struct Point{
  float x;
  float y;
};

/*
 * Bir cemberi ifade eder. 
 * Bir merkez noktasi ve yaricapi elemanlaridir. 
 */
struct Circle{
    float radius;
    struct Point center;
};


float float_rand( float min, float max );
double distance(struct Point *a, struct Point *b);
int is_in_circle(struct Point *a, struct Circle *c);
void create_point_array(struct Point *pt_array,int N);


#endif /* STRUCTPOINT_H_ */
