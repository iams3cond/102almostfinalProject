//Andrew Hunter
//CPSC 102

/* material.c */

#include "ray.h"


/**/
/* Create a new material description;   */
/* calls material_load_attributes().    */
/* Ignore the attrmax argument for now. */
void material_init(FILE *in, model_t *model, int attrmax)    
{
   /* malloc() a material_t structure, use memset() to */
   /* initialize it to 0, and store the MAT_COOKIE     */

   // --- CODE GOES HERE ---
    material_t *mat = malloc(sizeof(material_t));
    memset(mat, 0, sizeof(material_t));
    
    mat -> cookie = MAT_COOKIE;

   /* Load attributes as in camera.c                      */
   /* Unlike the camera, the number of attributes is      */
   /* optional. Attributes should be initialized to 0.0.  */

   material_load_attributes(in, mat);

   /* Ask list_add to add the material entity to the   */
   /* end of the mats list in the model structure.     */

   // --- CODE GOES HERE --- 
    list_add(model->mats, mat);
    
}


/**/
/* Read the info from the file that contains the attributes */ 
/* for the materials. Unlike camera, materials may have 1,  */
/* 2, or 3 attributes, so will not need to count the total  */
/* number of attributes that were read in.                  */
void material_load_attributes(FILE *in, material_t *mat)
{


   // --- CODE GOES HERE ---
    char attrib_name[16];
    int count = 0;
    
    count = fscanf(in, "%s", mat -> name);
    assert (count == 1);
    
    count = fscanf(in, "%s", attrib_name);
    assert(count == 1);
    assert(attrib_name[0] == '{');
    
    
    count = fscanf(in, "%s", attrib_name);
    assert(count == 1);
    while (attrib_name[0] != '}')
    {
        if (strcmp(attrib_name, "ambient") == 0)
        {
            count = fscanf(in, "%lf %lf %lf", &mat->ambient.r, &mat->ambient.g, &mat->ambient.b);

        }
        
        else if( strcmp( attrib_name, "diffuse" ) == 0 ){
            count = fscanf(in,"%lf %lf %lf", &mat->diffuse.r,&mat->diffuse.g, &mat ->diffuse.b);
            
        }
        
        else if(strcmp(attrib_name, "specular") == 0){
            count = fscanf(in,"%lf",&mat->specular);

            
        }
            else
            {
                fprintf(stderr, "Bad attribute: %s \n", attrib_name);
                exit(1);
            }
        fscanf(in, "%s", attrib_name);
    }
}
//poop



/**/
/* Search the materials list for the given name, for  */
/* example, if name is "yellow", search the list for  */
/* the material with that name.                       */ 
material_t *material_getbyname(model_t *model, char *name)    
{
    list_t *templist = NULL;
    link_t *templink = NULL;
    material_t *tempmat = NULL;

    templist = model->mats;
    templink=templist -> first;

    while(templink != NULL){

        tempmat=templink->entity;

        if(strcmp(tempmat->name,name) == 0){
            return tempmat;
        }

        templink=templink->next;
    }


    return NULL;

}


/**/
/* Print a material_t struct with the attributes read in      */
/* from the input file in the following format:  	           */ 
/* all keywords left justified in a field of 12 wide          */
/* int/float values - field width of 5; 1 place after decimal */
/*  
	material     green
	ambient        0.0   0.0   0.0
	diffuse        0.0   5.0   0.0
	specular       1.0
*/
/* This function is called from material_list_print() to */
/* print the values for each individual material (node). */
void material_print(material_t *mat, FILE *out)
{ 
   assert(mat->cookie == MAT_COOKIE);
  
   // --- CODE GOES HERE ---
    fprintf(out, "%-12s %-12s\n", "Material", mat->name);
    fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "Ambient", mat->ambient.r, mat->ambient.g, mat->ambient.b);
    fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "Diffuse", mat->diffuse.r, mat->diffuse.g, mat->diffuse.b);
    fprintf(out, "%-12s %5.1lf\n\n", "Specular", mat->specular);

}


/**/
/* Produce a formatted dump of the material list.  This */
/* funcion steps through the list of materials, and for */
/* each material (node) that it gets to, it calls the   */
/* material_print() function to actually print the      */
/* values of that material_t object.                    */
void material_list_print(model_t *model, FILE *out)
{

    list_t *templist = NULL;
    link_t *templink = NULL;
    material_t *tempmat = NULL;

    templist = model->mats;
    templink=templist -> first;

    while(templink != NULL){

        tempmat=templink->entity;
        material_print(tempmat,out);
        templink=templink->next;
    }
}


/**/
/* Copy the ambient values to the destination drgb_t.  */
void material_getambient(object_t *obj, material_t *mat, drgb_t *dest)   
{
   // --- CODE GOES HERE ---
    assert(mat->cookie == MAT_COOKIE);
    
    dest -> r = mat -> ambient.r;
    dest -> g = mat -> ambient.g;
    dest -> b = mat -> ambient.b;

}


/**/
/* Copy the diffuse values to the destination drgb_t.  */
void material_getdiffuse(object_t *obj, material_t *mat, drgb_t *dest)
{
   // --- CODE GOES HERE ---
    assert(mat->cookie == MAT_COOKIE);
    
    dest -> r = mat -> diffuse.r;
    dest -> g = mat -> diffuse.g;
    dest -> b = mat -> diffuse.b;
 
}


/**/
/* Return the specular value, rather than copy it to  */
/* a destination argument that will hold the value as */
/* with the above two functions.                      */
double material_getspecular(object_t *obj, material_t *mat)
{
   // --- CODE GOES HERE --- 
    
    return mat -> specular;

}
