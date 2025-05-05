#include <stdio.h>
#include <stdlib.h>
#include "malloc.h"
#include "image-io.h"
static void read_pgm_pixel_data(struct image *img)
{
    struct pam *pam = &img->pam;
    tuple *row = pnm_allocpamrow(pam);
    make_matrix(img->g, pam->height, pam->width);
    img->r = img->b = NULL;
    for (int i = 0; i < pam->height; i++)
    {
        pnm_readpamrow(pam, row);
        for (int j = 0; j < pam->width; j++)
            img->g[i][j] = row[j][0];
    }
    pnm_freepamrow(row);

}
static void read_ppm_pixel_data(struct image *img)
{
    if(img != NULL)
    {
        struct pam *pam = &img->pam;
        tuple *row = pnm_allocpamrow(pam);
        make_matrix(img->r, pam->height, pam->width);
        make_matrix(img->g, pam->height, pam->width);
        make_matrix(img->b, pam->height, pam->width);
        for (int i = 0; i < pam->height; i++)
        {
            pnm_readpamrow(pam, row);
            for (int j = 0; j < pam->width; j++)
            {
                img->r[i][j] = row[j][0];
                img->g[i][j] = row[j][1];
                img->b[i][j] = row[j][2];
            }
        }
        pnm_freepamrow(row);
    }
    else
    {
        fprintf(stderr, "The pointer is null you need to initialize it before you pass it");
    }
}
struct image *read_image(char *filename)
{
    struct image *img = xmalloc(sizeof *img);
    if(!img)
    {
        fprintf(stderr, "Memory allocation failed");
        return EXIT_FAILURE;
    }
    struct pam *pam = &img->pam;
    FILE *fileptr = pm_openr(filename);
    pnm_readpaminit(fileptr, pam, sizeof(struct pam));
    if (pam->format == PGM_FORMAT || pam->format == RPGM_FORMAT)
        read_pgm_pixel_data(img);
    else if (pam->format == PPM_FORMAT || pam->format == RPPM_FORMAT)
        read_ppm_pixel_data(img);
    else
    {
        fprintf(stderr, "error: file '%s' contains neither a PGM nor a PPM image\n", filename);
        exit(EXIT_FAILURE);
    }
    pm_close(fileptr);
    return img;
};
static void write_pgm_pixel_data(struct image *img)
{
    struct pam *pam = &img->pam;
    tuple *row = pnm_allocpamrow(pam);
    for (int i = 0; i < pam->height; i++)
    {
        for (int j = 0; j < pam->width; j++)
            row[j][0] = img->g[i][j];
        pnm_writepamrow(pam, row);
    }
    pnm_freepamrow(row);
}
static void write_ppm_pixel_data(struct image *img)
{
    struct pam *pam = &img->pam;
    tuple *row = pnm_allocpamrow(pam);
    for (int i = 0; i < pam->height; i++)
    {
        for (int j = 0; j < pam->width; j++)
        {
            row[j][0] = img->r[i][j];
            row[j][1] = img->g[i][j];
            row[j][2] = img->b[i][j];
        }
        pnm_writepamrow(pam, row);
    }
    pnm_freepamrow(row);
}
void write_image(char *filename, struct image *img)
{
    struct pam *pam = &img->pam;
    pam->file = pm_openw(filename);
    pam->plainformat= (pam->format==PGM_FORMAT || pam->format == PPM_FORMAT) ? 1 : 0;//If the image is a PPM or a PGM format return 1 else 0
    pnm_writepaminit(pam);
    if(pam->format == PGM_FORMAT || pam->format == RPGM_FORMAT)
    {
        write_pgm_pixel_data(img);
    }
    else if(pam->format == PPM_FORMAT || pam->format == RPPM_FORMAT)// I learn't control flow with this statement right here
    {
        write_ppm_pixel_data(img);
    }
    else
    {
        fprintf(stderr, "error: file %s, line %d: shouldn't be here!\n",
                __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    pm_close(pam->file);
}


void free_image(struct image *img)
{
    if (img != NULL)
    {
        free_matrix(img->r);
        free_matrix(img->g);
        free_matrix(img->b);
        free(img);
    }

}

