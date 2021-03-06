//Andrew Hunter
//CPSC 102

/*  raytrace.c  */

/*  find_closest_object() function
    arguments:
       model_t *model - the model structure
       vect_t *base - base of the ray (viewpoint)
       vect_t *dir - unit direction vector of the ray
       object_t *last_hit - the last hit object
       double *retdist - store distance to the hit point here

     	 if no object is hit, then retdist will have the value -1, 
	       and NULL will be returned 
		 if an object is hit, retdist will end up with the mindist
		    and minobj will be a non-NULL object that is returned 
*/


#include "ray.h"


object_t *find_closest_object(model_t  *model, vec_t  *base, vec_t  *dir,
                              object_t  *last_hit, double  *retdist)     {
   
   list_t *list = model->objs;
   list_reset(list);
   double dist;
   
   object_t  *minobj = NULL;
   double mindist = -1.0;
   
   assert(list->first != NULL);
   object_t *tobj = list_get_entity(list);
   assert (tobj != NULL);
   
   while (list_not_end(list)==1)
   {
           //dist = tobj->hits(tobj,base, dir);
           if(tobj == last_hit)
           {
                   list_next_link(list);
                   tobj = list_get_entity(list);
                   
           }
           //dist = tobj->hits(tobj,base, dir);
           else
           {
               dist = tobj->hits(tobj,base, dir);
               
               if  ((dist >= 0) && ((minobj == NULL)||(dist < mindist)))
               {
                  mindist = dist;
                  minobj = tobj;
                  }
           }
           
           
           list_next_link(list);
           
           if(list_not_end(list) ==1)
           {
             tobj = list_get_entity(list);
           }
           
       
   }
   
   *retdist = mindist;
   return(minobj);

}    

        




