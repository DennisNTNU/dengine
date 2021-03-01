#ifndef OBJ_IMPORT_H
#define OBJ_IMPORT_H

/**
 *
 * \param positions Always a multiple of three (x,y,z)
 * \param uvs Always a multiple of two (u,v)
 */
int importObj(const char* path, float** positions, float** uvs, float** normals,
              int* vertex_count, unsigned int** indices, unsigned int* index_count);

void test_parse_obj();

#endif /* OBJ_IMPORT_H */
