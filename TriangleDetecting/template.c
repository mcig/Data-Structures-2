#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX 5
#define GENERATEMAX 5

typedef struct Coordinate {
	int x, y;
} COORD_t[1], *COORD;

typedef struct Location {
	int label;
	double area;
	COORD coord;
} LOC_t[1], *LOC;

LOC init_location() {
	LOC l = malloc(sizeof(LOC_t));
	l->label = -1;
	l->area = 0.0;

	return l;
}

LOC **init_location_arr(int size) {
	LOC **new_arr;
	int i, j;

	new_arr = malloc(sizeof(LOC) * size);
	for (i = 0; i < size; ++i) {
		new_arr[i] = malloc(sizeof(LOC));
		for (j = 0; j < 3; ++j) {
			new_arr[i][j] = init_location();
		}
	}

	return new_arr;
}

COORD init_cordination() {
	return malloc(sizeof(COORD_t));
}

void free_triangles(LOC **loc_arr, int N) {
	int i;
	while (N) {
		for (i = 0; i < 2; i++)
			free(loc_arr[N][i]);
		N--;
	}
	free(loc_arr);
}

void print_coords(LOC *arr){
	printf("P1 - x: %d y: %d\n",arr[0]->coord->x,arr[0]->coord->y);
	printf("P2 - x: %d y: %d\n",arr[1]->coord->x,arr[1]->coord->y);
	printf("P3 - x: %d y: %d\n",arr[2]->coord->x,arr[2]->coord->y);
}

void print_triangles(LOC *arr) {
	if(arr[0]->area != 0.0){
		printf("Triangle of area %f is detected, points are:\n",arr[0]->area);
		print_coords(arr);
	}
}

void print_nontria(LOC *arr) {
	if(arr[0]->area == 0.0){
		printf("Non Triangular points are:\n");
		print_coords(arr);
	}
}


int gen_number() {
	return (rand() % GENERATEMAX);
}

int is_dublicate(LOC *arr) {
	int i;
	for(i=0;i<2;i++){
		if(arr[i]->coord->x == arr[i+1]->coord->x && arr[i]->coord->y == arr[i+1]->coord->y)
			return 1;
	}
	return -1;
}

void copy_coords(COORD coordObj, LOC locationObj){//helper
	coordObj->x = locationObj->coord->x;
	coordObj->y = locationObj->coord->y;
}

int check_is_triangle(LOC *temp_arr, double *ptr_area) {
	if(is_dublicate(temp_arr)== 1)
		return -1;
	COORD_t first,second,third;
	copy_coords(first,temp_arr[0]);
	copy_coords(second,temp_arr[1]);
	copy_coords(third,temp_arr[2]);

	double area = 0.5 * ((first->x * (second->y - third->y))
			+ (second->x * (third->y - first->y))
			+ (third->x * (first->y - second->y)));

	if(area < 0.0){
		area = -area;
	}

	if(area == 0)
		return -1;
	else{
		*ptr_area = area;
		return 1;
	}
}

void generate_triangles(LOC **tri_arr, int noftria) {
	int i,j;
	for(i=0;i<noftria;i++){
		for(j=0;j<3;j++){
			tri_arr[i][j]->label = i;
			tri_arr[i][j]->coord = init_cordination();
			tri_arr[i][j]->coord->x = gen_number();
			tri_arr[i][j]->coord->y = gen_number();
		}
		check_is_triangle(tri_arr[i],&tri_arr[i][0]->area);
	}
}

int main() {
	srand(time(NULL));
	int i, noftria = 5;
	LOC **tria_arr;

	tria_arr = init_location_arr(noftria);

	generate_triangles(tria_arr, noftria);

	for (i = 0; i < noftria; ++i) {
		print_triangles(tria_arr[i]);
	}
	printf("\n ********************** \n");
	for (i = 0; i < noftria; ++i) {
		print_nontria(tria_arr[i]);
	}

	free_triangles(tria_arr, noftria-1);

	return 0;
}

