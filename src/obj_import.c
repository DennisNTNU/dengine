#include "obj_import.h"

#include <stdio.h>
#include <string.h> // for memset(), strtok_r()
#include <errno.h> // for ENOENT
#include <sys/stat.h> // for stat()
#include <stdlib.h> // for malloc()

struct __attribute__((packed)) Position
{
    float x;
    float y;
    float z;
};

struct __attribute__((packed)) Uv
{
    float u;
    float v;
};

struct __attribute__((packed)) Normal
{
    float x;
    float y;
    float z;
};

// gets character count until and not including next newline
static void get_chars_until_newline(char* str, int* line_size)
{
    *line_size = 0;
    while (str[*line_size])
    {
        if (str[(*line_size)++] == '\n')
        {
            return;
        }
    }
}

static int read_text_file(const char* path, char** file_buffer)
{
    struct stat st;
    if (stat(path, &st) != 0)
    {
        return errno;
    }

    FILE* obj_input_file_p = fopen(path, "r");
    if (obj_input_file_p == NULL)
    {
        return ENOENT;
    }

    size_t file_buffer_size = st.st_size;
    *file_buffer = malloc(file_buffer_size+1); // +1 for null termination
    if (*file_buffer == NULL)
    {
        return -1;
    }

    int nread = fread(*file_buffer, 1, file_buffer_size, obj_input_file_p);
    if (nread != file_buffer_size)
    {
        free(*file_buffer);
        return errno;
    }
    (*file_buffer)[file_buffer_size] = 0; // null terminating

    fclose(obj_input_file_p);

    return 0;
}

int parse_obj(char* obj_file, float** positions, float** uvs, float** normals,
              int* vertex_count, unsigned int** indices, unsigned int* index_count)
{
    int v_s = 0;
    int vt_s = 0;
    int vn_s = 0;
    int f_s = 0;
    *vertex_count = 0;

    // counting v's, vt's, vn's and f's
    int str_index = 0;
    char line[512] = "";
    while (1)
    {
        int line_size = 0;
        char* line = &(obj_file[str_index]);
        get_chars_until_newline(line, &line_size);
        if (line_size == 0)
        {
            break;
        }

        if (line[0] == 'v')
        {
            if (line[1] == ' ')
            {
                v_s++;
            }
            else if (line[1] == 't')
            {
                vt_s++;
            }
            else if (line[1] == 'n')
            {
                vn_s++;
            }
        }
        else if (line[0] == 'f')
        {
            f_s++;
        }
        str_index += line_size;
    }

    *index_count = 3*f_s;
    *vertex_count = *index_count;

    printf("v's: %i, vt's: %i, vn's: %i, f's: %i\nvcount: %i\n", v_s, vt_s, vn_s, f_s, *vertex_count);

    // allocating buffers output buffers
    *indices = malloc(sizeof(int)*(*index_count));
    *positions = malloc(sizeof(struct Position)*(*vertex_count));
    if (vt_s > 0)
    {
        *uvs = malloc(sizeof(struct Uv)*(*vertex_count));
    }
    else
    {
        *uvs = NULL;
    }
    if (vn_s > 0)
    {
        *normals = malloc(sizeof(struct Normal)*(*vertex_count));
    }
    else
    {
        *normals = 0;
    }
    
    // allocating input buffers
    struct Position* poses = malloc(sizeof(struct Position)*v_s);
    struct Uv* uv_s = malloc(sizeof(struct Position)*vt_s);
    struct Normal* norms = malloc(sizeof(struct Normal)*vn_s);

    // reading model data: v's, vt's and vn's, into input buffers
    int v_index = 0;
    int vt_index = 0;
    int vn_index = 0;
    str_index = 0;
    while (1)
    {
        int line_size = 0;
        char* line = &(obj_file[str_index]);
        get_chars_until_newline(line, &line_size);
        if (line_size == 0)
        {
            break;
        }

        if (line[0] == 'v')
        {
            if (line[1] == ' ')
            {
                if (sscanf(line, "v %f %f %f", &(poses[v_index].x), &(poses[v_index].y), &(poses[v_index].z)) != 3)
                {
                    printf("Error parsing v\n");
                }

                //printf("%f %f %f\n", poses[v_index].x, poses[v_index].y, poses[v_index].z);
                v_index++;
            }
            else if (line[1] == 't')
            {
                if (sscanf(line, "vt %f %f", &(uv_s[vt_index].u), &(uv_s[vt_index].v)) != 2)
                {
                    printf("Error parsing vt\n");
                }
                vt_index++;
            }
            else if (line[1] == 'n')
            {
                if (sscanf(line, "vn %f %f %f", &(norms[vn_index].x), &(norms[vn_index]).y, &(norms[vn_index].z)) != 3)
                {
                    printf("Error parsing vn\n");
                }
                vn_index++;
            }
        }
        else if (line[0] == 'f')
        {
            break;
        }
        str_index += line_size;
    }

    // parsing face indices, copying input buffers into output buffers
    int vertex_index = 0;
    while (1)
    {
        int line_size = 0;
        char* line = &(obj_file[str_index]);
        get_chars_until_newline(line, &line_size);
        if (line_size == 0)
        {
            break;
        }

        if (line[0] == 'f')
        {
            int face_index_count = 0;
            int face_indices[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
            if ((face_index_count = sscanf(line, "f %i/%i/%i %i/%i/%i %i/%i/%i",
                &(face_indices[0]), &(face_indices[1]), &(face_indices[2]), &(face_indices[3]), &(face_indices[4]),
                &(face_indices[5]), &(face_indices[6]), &(face_indices[7]), &(face_indices[8]))) == 9)
            {
                // vertex position indices = 0, 3, 6
                memcpy(&((*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]),
                       &(poses[face_indices[0]-1]), sizeof(struct Position));
                memcpy(&((*uvs)[vertex_index*sizeof(struct Uv)/sizeof(float)]),
                       &(uv_s[face_indices[1]-1]), sizeof(struct Uv));
                memcpy(&(*normals)[vertex_index*sizeof(struct Normal)/sizeof(float)], 
                       &(norms[face_indices[2]-1]), sizeof(struct Normal));
                (*indices)[vertex_index] = vertex_index;

/*
                printf("%f %f %f\n", (*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]
                                   , (*positions)[vertex_index*sizeof(struct Position)/sizeof(float) + 1]
                                   , (*positions)[vertex_index*sizeof(struct Position)/sizeof(float) + 2]);
*/

                vertex_index++;

                memcpy(&((*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]),
                       &(poses[face_indices[3]-1]), sizeof(struct Position));
                memcpy(&((*uvs)[vertex_index*sizeof(struct Uv)/sizeof(float)]),
                       &(uv_s[face_indices[4]-1]), sizeof(struct Uv));
                memcpy(&(*normals)[vertex_index*sizeof(struct Normal)/sizeof(float)], 
                       &(norms[face_indices[5]-1]), sizeof(struct Normal));
                (*indices)[vertex_index] = vertex_index;

/*
                printf("%f %f %f\n", (*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]
                                   , (*positions)[vertex_index*sizeof(struct Position)/sizeof(float) + 1]
                                   , (*positions)[vertex_index*sizeof(struct Position)/sizeof(float) + 2]);
*/

                vertex_index++;

                memcpy(&((*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]),
                       &(poses[face_indices[6]-1]), sizeof(struct Position));
                memcpy(&((*uvs)[vertex_index*sizeof(struct Uv)/sizeof(float)]),
                       &(uv_s[face_indices[7]-1]), sizeof(struct Uv));
                memcpy(&(*normals)[vertex_index*sizeof(struct Normal)/sizeof(float)], 
                       &(norms[face_indices[8]-1]), sizeof(struct Normal));
                (*indices)[vertex_index] = vertex_index;

/*
                printf("%f %f %f\n", (*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]
                                   , (*positions)[vertex_index*sizeof(struct Position)/sizeof(float) + 1]
                                   , (*positions)[vertex_index*sizeof(struct Position)/sizeof(float) + 2]);*/


                vertex_index++;

            }
            else if ((face_index_count = sscanf(line, "f %i/%i %i/%i %i/%i",
                    &(face_indices[0]), &(face_indices[1]), &(face_indices[2]), &(face_indices[3]),
                    &(face_indices[4]), &(face_indices[5]))) == 6)
            {
                // vertex position indices = 0, 2, 4
                memcpy(&((*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]),
                       &(poses[face_indices[0]-1]), sizeof(struct Position));
                memcpy(&((*uvs)[vertex_index*sizeof(struct Uv)/sizeof(float)]),
                       &(uv_s[face_indices[1]-1]), sizeof(struct Uv));
                (*indices)[vertex_index] = vertex_index;
                vertex_index++;

                memcpy(&((*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]),
                       &(poses[face_indices[2]-1]), sizeof(struct Position));
                memcpy(&((*uvs)[vertex_index*sizeof(struct Uv)/sizeof(float)]),
                       &(uv_s[face_indices[3]-1]), sizeof(struct Uv));
                (*indices)[vertex_index] = vertex_index;
                vertex_index++;

                memcpy(&((*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]),
                       &(poses[face_indices[4]-1]), sizeof(struct Position));
                memcpy(&((*uvs)[vertex_index*sizeof(struct Uv)/sizeof(float)]),
                       &(uv_s[face_indices[5]-1]), sizeof(struct Uv));
                (*indices)[vertex_index] = vertex_index;
                vertex_index++;

            }
            else if ((face_index_count = sscanf(line, "f %i %i %i",
                    &(face_indices[0]), &(face_indices[1]), &(face_indices[2]))) == 3)
            {
                // vertex position indices = 0, 1, 2
                memcpy(&((*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]),
                       &(poses[face_indices[0]-1]), sizeof(struct Position));
                (*indices)[vertex_index] = vertex_index;
                vertex_index++;

                memcpy(&((*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]),
                       &(poses[face_indices[1]-1]), sizeof(struct Position));
                (*indices)[vertex_index] = vertex_index;
                vertex_index++;

                memcpy(&((*positions)[vertex_index*sizeof(struct Position)/sizeof(float)]),
                       &(poses[face_indices[2]-1]), sizeof(struct Position));
                (*indices)[vertex_index] = vertex_index;
                vertex_index++;

            }
            else
            {
            	printf("Error parsing f, %i\n", face_index_count);
            }
        }
        str_index += line_size;
    }

    free(poses);
    free(uv_s);
    free(norms);

    return 0;
}



int importObj(const char* path, float** positions, float** uvs, float** normals,
              int* vertex_count, unsigned int** indices, unsigned int* index_count)
{
    char* obj_file = NULL;
    int ret = read_text_file(path, &obj_file);
    if (ret != 0)
    {
        return ret;
    }

    ret = parse_obj(obj_file, positions, uvs, normals, vertex_count, indices, index_count);

    free(obj_file);

    return ret;
}








void test_parse_obj()
{
    char test_obj_file[] = "# Blender v2.91.0 OBJ File: ''\n"
                           "# www.blender.org\n"
                           "o Plane\n"
                           "v -1.000000 0.000000 1.000000\n"
                           "v 1.000000 0.000000 1.000000\n"
                           "v -1.000000 0.000000 -1.000000\n"
                           "v 1.000000 0.000000 -1.000000\n"
                           "vt 1.000000 0.000000\n"
                           "vt 0.000000 1.000000\n"
                           "vt 0.000000 0.000000\n"
                           "vt 1.000000 1.000000\n"
                           "vn 0.0000 1.0000 0.0000\n"
                           "s off\n"
                           "f 2/1/1 3/2/1 1/3/1\n"
                           "f 2/1/1 4/4/1 3/2/1\n";

    char* correct_v_output[] = {"1.000000 0.000000 1.000000",
                                "-1.000000 0.000000 -1.000000",
                                "-1.000000 0.000000 1.000000",
                                "1.000000 0.000000 1.000000",
                                "1.000000 0.000000 -1.000000",
                                "-1.000000 0.000000 -1.000000"};
    char* correct_vt_output[] = {"1.000000 0.000000",
                                 "0.000000 1.000000",
                                 "0.000000 0.000000",
                                 "1.000000 0.000000",
                                 "1.000000 1.000000",
                                 "0.000000 1.000000"};


    unsigned int* indices = NULL;
    float* vertexPositions = NULL;
    float* vertexUVs = NULL;
    float* vertexNormals = NULL;
    int vertexCount = 0;
    int indexCount = 0;

    //initData(&indices, &vertexPositions, &vertexUVs, &vertexCount);
    int ret = parse_obj(test_obj_file, &vertexPositions, &vertexUVs, &vertexNormals, &vertexCount, &indices, &indexCount);

    for (int i = 0; i < vertexCount; i++)
    {
        printf("\nv%i |%f %f %f\n", i, vertexPositions[3*i + 0]
                                     , vertexPositions[3*i + 1]
                                     , vertexPositions[3*i + 2]);
        if (i < 6)
        {
            printf("   |%s\n", correct_v_output[i]);
        }
    }
    printf("If the line pairs above match, parsing of positions went ok\n");

    for (int i = 0; i < vertexCount; i++)
    {
        printf("\nv%i |%f %f\n", i, vertexUVs[2*i + 0]
                                  , vertexUVs[2*i + 1]);
        if (i < 6)
        {
            printf("   |%s\n", correct_vt_output[i]);
        }
    }
    printf("If the line pairs above match, parsing of uvs went ok\n\n");
}