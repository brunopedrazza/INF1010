#include "set.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	Set* s1 = setCreate();
	Set* s2 = setCreate();
	Set *t1, *t2, *t3;
	
	setInsert(s1, 10); 	setInsert(s1, 13); 	setInsert(s1, 20);
	setInsert(s1, 25); 	setInsert(s1, 28); 	setInsert(s1, 30);
	setShow("s1", s1);

	setRemove(s1, 25);
	setShow("s1 com 25 removido", s1);

	setInsert(s2, 5); 	setInsert(s2, 10); 	setInsert(s2, 20);
	setInsert(s2, 21); 	setInsert(s2, 24); 	setInsert(s2, 28);
	setShow("s2", s2);
	
        
	t1 = setUnion(s1, s2);
	setShow("s1Us2", t1);
	
	t1 = setIntersection(s1, s2);   
	setShow("s1Is2", t1);
        t1 = setDestroy (t1);
	
	t1 = setDifference(s1, s2);   
        printf ("nÃºmero de elementos em s1-s2: %d\n", setNumberOfElements(t1));
	setShow("s1-s2", t1);

        t2 = setDifference(s2, s1); 
        printf ("nÃºmero de elementos em s2-s1: %d\n", setNumberOfElements(t2));
	setShow("s2-s1", t2);

        t3 = setDifference(s1, s1); 
        printf ("nÃºmero de elementos em s1-s1: %d\n", setNumberOfElements(t3));
	setShow("s1-s1", t3);
        t3 = setDestroy(t3);
     
        t3 = setUnion (t1, t2);
        t1 = setDestroy (t1);
        t2 = setDestroy(t2);
        t1 = setIntersection(s1,s2);
        t2 = setUnion (t1, t3);
        t1 = setDestroy(t1);
        t1 = setUnion (s1, s2);
        
        printf ("(s1-s2) U (s2-s1) U (s1 I s2) = s1Us2? %s\n", setIsEqual(t1, t2)?"sim":"nÃ£o");

	s1 = setDestroy(s1);
	s2 = setDestroy(s2);
        t1 = setDestroy (t1);
        t2 = setDestroy(t2);
        t3 = setDestroy(t3);

	return 0;
}

