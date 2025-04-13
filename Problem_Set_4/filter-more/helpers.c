#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average =
                (float) (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = (int) round(average);
            image[i][j].rgbtGreen = (int) round(average);
            image[i][j].rgbtRed = (int) round(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE row[width];
        for (int j = 0; j < width; j++)
        {
            row[j] = image[i][j];
        }
        for (int j = 0; j < width; j++)
        {
            image[i][j] = row[width - 1 - j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                float average_blue =
                    (float) (copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                             copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                    4.0;
                float average_green =
                    (float) (copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                             copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                    4.0;
                float average_red = (float) (copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                    4.0;
                image[i][j].rgbtBlue = (int) round(average_blue);
                image[i][j].rgbtGreen = (int) round(average_green);
                image[i][j].rgbtRed = (int) round(average_red);
            }
            else if (i == 0 && j == width - 1)
            {
                float average_blue =
                    (float) (copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                             copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) /
                    4.0;
                float average_green =
                    (float) (copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                             copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) /
                    4.0;
                float average_red = (float) (copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) /
                                    4.0;
                image[i][j].rgbtBlue = (int) round(average_blue);
                image[i][j].rgbtGreen = (int) round(average_green);
                image[i][j].rgbtRed = (int) round(average_red);
            }
            else if (i == height - 1 && j == 0)
            {
                float average_blue =
                    (float) (copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                             copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) /
                    4.0;
                float average_green =
                    (float) (copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                             copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                    4.0;
                float average_red = (float) (copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) /
                                    4.0;
                image[i][j].rgbtBlue = (int) round(average_blue);
                image[i][j].rgbtGreen = (int) round(average_green);
                image[i][j].rgbtRed = (int) round(average_red);
            }
            else if (i == height - 1 && j == width - 1)
            {
                float average_blue =
                    (float) (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                             copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue) /
                    4.0;
                float average_green =
                    (float) (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                             copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen) /
                    4.0;
                float average_red = (float) (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) /
                                    4.0;
                image[i][j].rgbtBlue = (int) round(average_blue);
                image[i][j].rgbtGreen = (int) round(average_green);
                image[i][j].rgbtRed = (int) round(average_red);
            }
            else if (i == 0)
            {
                float average_blue =
                    (float) (copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                             copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                             copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                    6.0;
                float average_green =
                    (float) (copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                             copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                             copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                    6.0;
                float average_red = (float) (copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                    6.0;
                image[i][j].rgbtBlue = (int) round(average_blue);
                image[i][j].rgbtGreen = (int) round(average_green);
                image[i][j].rgbtRed = (int) round(average_red);
            }
            else if (i == height - 1)
            {
                float average_blue =
                    (float) (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                             copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                             copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) /
                    6.0;
                float average_green =
                    (float) (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                             copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                             copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                    6.0;
                float average_red = (float) (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) /
                                    6.0;
                image[i][j].rgbtBlue = (int) round(average_blue);
                image[i][j].rgbtGreen = (int) round(average_green);
                image[i][j].rgbtRed = (int) round(average_red);
            }
            else if (j == 0)
            {
                float average_blue =
                    (float) (copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                             copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                             copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                    6.0;
                float average_green =
                    (float) (copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                             copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                             copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                    6.0;
                float average_red = (float) (copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                    6.0;
                image[i][j].rgbtBlue = (int) round(average_blue);
                image[i][j].rgbtGreen = (int) round(average_green);
                image[i][j].rgbtRed = (int) round(average_red);
            }
            else if (j == width - 1)
            {
                float average_blue =
                    (float) (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                             copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                             copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) /
                    6.0;
                float average_green =
                    (float) (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                             copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                             copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) /
                    6.0;
                float average_red = (float) (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) /
                                    6.0;
                image[i][j].rgbtBlue = (int) round(average_blue);
                image[i][j].rgbtGreen = (int) round(average_green);
                image[i][j].rgbtRed = (int) round(average_red);
            }
            else
            {
                float average_blue =
                    (float) (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                             copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                             copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                             copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                             copy[i + 1][j + 1].rgbtBlue) /
                    9.0;
                float average_green =
                    (float) (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                             copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                             copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                             copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                             copy[i + 1][j + 1].rgbtGreen) /
                    9.0;
                float average_red = (float) (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                             copy[i + 1][j + 1].rgbtRed) /
                                    9.0;
                image[i][j].rgbtBlue = (int) round(average_blue);
                image[i][j].rgbtGreen = (int) round(average_green);
                image[i][j].rgbtRed = (int) round(average_red);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int G[3];
            int Gx[3];
            int Gy[3];

            if (i == 0 && j == 0)
            {
                Gx[0] = copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 2 +
                        copy[i + 1][j].rgbtBlue * 0 + copy[i + 1][j + 1].rgbtBlue * 1;
                Gy[0] = copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 0 +
                        copy[i + 1][j].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue * 1;
                Gx[1] = copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 2 +
                        copy[i + 1][j].rgbtGreen * 0 + copy[i + 1][j + 1].rgbtGreen * 1;
                Gy[1] = copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 0 +
                        copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen * 1;
                Gx[2] = copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 2 +
                        copy[i + 1][j].rgbtRed * 0 + copy[i + 1][j + 1].rgbtRed * 1;
                Gy[2] = copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 0 +
                        copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed * 1;
            }
            else if (i == 0 && j == width - 1)
            {
                Gx[0] = copy[i][j - 1].rgbtBlue * -2 + copy[i][j].rgbtBlue * 0 +
                        copy[i + 1][j - 1].rgbtBlue * -1 + copy[i + 1][j].rgbtBlue * 0;
                Gy[0] = copy[i][j - 1].rgbtBlue * 0 + copy[i][j].rgbtBlue * 0 +
                        copy[i + 1][j - 1].rgbtBlue * 1 + copy[i + 1][j].rgbtBlue * 2;
                Gx[1] = copy[i][j - 1].rgbtGreen * -2 + copy[i][j].rgbtGreen * 0 +
                        copy[i + 1][j - 1].rgbtGreen * -1 + copy[i + 1][j].rgbtGreen * 0;
                Gy[1] = copy[i][j - 1].rgbtGreen * 0 + copy[i][j].rgbtGreen * 0 +
                        copy[i + 1][j - 1].rgbtGreen * 1 + copy[i + 1][j].rgbtGreen * 2;
                Gx[2] = copy[i][j - 1].rgbtRed * -2 + copy[i][j].rgbtRed * 0 +
                        copy[i + 1][j - 1].rgbtRed * -1 + copy[i + 1][j].rgbtRed * 0;
                Gy[2] = copy[i][j - 1].rgbtRed * 0 + copy[i][j].rgbtRed * 0 +
                        copy[i + 1][j - 1].rgbtRed * 1 + copy[i + 1][j].rgbtRed * 2;
            }
            else if (i == height - 1 && j == 0)
            {
                Gx[0] = copy[i - 1][j].rgbtBlue * 0 + copy[i - 1][j + 1].rgbtBlue * 1 +
                        copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 2;
                Gy[0] = copy[i - 1][j].rgbtBlue * -2 + copy[i - 1][j + 1].rgbtBlue * -1 +
                        copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 0;
                Gx[1] = copy[i - 1][j].rgbtGreen * 0 + copy[i - 1][j + 1].rgbtGreen * 1 +
                        copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 2;
                Gy[1] = copy[i - 1][j].rgbtGreen * -2 + copy[i - 1][j + 1].rgbtGreen * -1 +
                        copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 0;
                Gx[2] = copy[i - 1][j].rgbtRed * 0 + copy[i - 1][j + 1].rgbtRed * 1 +
                        copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 2;
                Gy[2] = copy[i - 1][j].rgbtRed * -2 + copy[i - 1][j + 1].rgbtRed * -1 +
                        copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 0;
            }
            else if (i == height - 1 && j == width - 1)
            {
                Gx[0] = copy[i - 1][j - 1].rgbtBlue * -1 + copy[i - 1][j].rgbtBlue * 0 +
                        copy[i][j - 1].rgbtBlue * -2 + copy[i][j].rgbtBlue * 0;
                Gy[0] = copy[i - 1][j - 1].rgbtBlue * -1 + copy[i - 1][j].rgbtBlue * -2 +
                        copy[i][j - 1].rgbtBlue * 0 + copy[i][j].rgbtBlue * 0;
                Gx[1] = copy[i - 1][j - 1].rgbtGreen * -1 + copy[i - 1][j].rgbtGreen * 0 +
                        copy[i][j - 1].rgbtGreen * -2 + copy[i][j].rgbtGreen * 0;
                Gy[1] = copy[i - 1][j - 1].rgbtGreen * -1 + copy[i - 1][j].rgbtGreen * -2 +
                        copy[i][j - 1].rgbtGreen * 0 + copy[i][j].rgbtGreen * 0;
                Gx[2] = copy[i - 1][j - 1].rgbtRed * -1 + copy[i - 1][j].rgbtRed * 0 +
                        copy[i][j - 1].rgbtRed * -2 + copy[i][j].rgbtRed * 0;
                Gy[2] = copy[i - 1][j - 1].rgbtRed * -1 + copy[i - 1][j].rgbtRed * -2 +
                        copy[i][j - 1].rgbtRed * 0 + copy[i][j].rgbtRed * 0;
            }
            else if (i == 0)
            {
                Gx[0] = copy[i][j - 1].rgbtBlue * -2 + copy[i][j].rgbtBlue * 0 +
                        copy[i][j + 1].rgbtBlue * 2 + copy[i + 1][j - 1].rgbtBlue * -1 +
                        copy[i + 1][j].rgbtBlue * 0 + copy[i + 1][j + 1].rgbtBlue * 1;
                Gy[0] = copy[i][j - 1].rgbtBlue * 0 + copy[i][j].rgbtBlue * 0 +
                        copy[i][j + 1].rgbtBlue * 0 + copy[i + 1][j - 1].rgbtBlue * 1 +
                        copy[i + 1][j].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue * 1;
                Gx[1] = copy[i][j - 1].rgbtGreen * -2 + copy[i][j].rgbtGreen * 0 +
                        copy[i][j + 1].rgbtGreen * 2 + copy[i + 1][j - 1].rgbtGreen * -1 +
                        copy[i + 1][j].rgbtGreen * 0 + copy[i + 1][j + 1].rgbtGreen * 1;
                Gy[1] = copy[i][j - 1].rgbtGreen * 0 + copy[i][j].rgbtGreen * 0 +
                        copy[i][j + 1].rgbtGreen * 0 + copy[i + 1][j - 1].rgbtGreen * 1 +
                        copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen * 1;
                Gx[2] = copy[i][j - 1].rgbtRed * -2 + copy[i][j].rgbtRed * 0 +
                        copy[i][j + 1].rgbtRed * 2 + copy[i + 1][j - 1].rgbtRed * -1 +
                        copy[i + 1][j].rgbtRed * 0 + copy[i + 1][j + 1].rgbtRed * 1;
                Gy[2] = copy[i][j - 1].rgbtRed * 0 + copy[i][j].rgbtRed * 0 +
                        copy[i][j + 1].rgbtRed * 0 + copy[i + 1][j - 1].rgbtRed * 1 +
                        copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed * 1;
            }
            else if (i == height - 1)
            {
                Gx[0] = copy[i - 1][j - 1].rgbtBlue * -1 + copy[i - 1][j].rgbtBlue * 0 +
                        copy[i - 1][j + 1].rgbtBlue * 1 + copy[i][j - 1].rgbtBlue * -2 +
                        copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 2;
                Gy[0] = copy[i - 1][j - 1].rgbtBlue * -1 + copy[i - 1][j].rgbtBlue * -2 +
                        copy[i - 1][j + 1].rgbtBlue * -1 + copy[i][j - 1].rgbtBlue * 0 +
                        copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 0;
                Gx[1] = copy[i - 1][j - 1].rgbtGreen * -1 + copy[i - 1][j].rgbtGreen * 0 +
                        copy[i - 1][j + 1].rgbtGreen * 1 + copy[i][j - 1].rgbtGreen * -2 +
                        copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 2;
                Gy[1] = copy[i - 1][j - 1].rgbtGreen * -1 + copy[i - 1][j].rgbtGreen * -2 +
                        copy[i - 1][j + 1].rgbtGreen * -1 + copy[i][j - 1].rgbtGreen * 0 +
                        copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 0;
                Gx[2] = copy[i - 1][j - 1].rgbtRed * -1 + copy[i - 1][j].rgbtRed * 0 +
                        copy[i - 1][j + 1].rgbtRed * 1 + copy[i][j - 1].rgbtRed * -2 +
                        copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 2;
                Gy[2] = copy[i - 1][j - 1].rgbtRed * -1 + copy[i - 1][j].rgbtRed * -2 +
                        copy[i - 1][j + 1].rgbtRed * -1 + copy[i][j - 1].rgbtRed * 0 +
                        copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 0;
            }
            else if (j == 0)
            {
                Gx[0] = copy[i - 1][j].rgbtBlue * 0 + copy[i - 1][j + 1].rgbtBlue * 1 +
                        copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 2 +
                        copy[i + 1][j].rgbtBlue * 0 + copy[i + 1][j + 1].rgbtBlue * 1;
                Gy[0] = copy[i - 1][j].rgbtBlue * -2 + copy[i - 1][j + 1].rgbtBlue * -1 +
                        copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 0 +
                        copy[i + 1][j].rgbtBlue * 2 + copy[i + 1][j + 1].rgbtBlue * 1;
                Gx[1] = copy[i - 1][j].rgbtGreen * 0 + copy[i - 1][j + 1].rgbtGreen * 1 +
                        copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 2 +
                        copy[i + 1][j].rgbtGreen * 0 + copy[i + 1][j + 1].rgbtGreen * 1;
                Gy[1] = copy[i - 1][j].rgbtGreen * -2 + copy[i - 1][j + 1].rgbtGreen * -1 +
                        copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 0 +
                        copy[i + 1][j].rgbtGreen * 2 + copy[i + 1][j + 1].rgbtGreen * 1;
                Gx[2] = copy[i - 1][j].rgbtRed * 0 + copy[i - 1][j + 1].rgbtRed * 1 +
                        copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 2 +
                        copy[i + 1][j].rgbtRed * 0 + copy[i + 1][j + 1].rgbtRed * 1;
                Gy[2] = copy[i - 1][j].rgbtRed * -2 + copy[i - 1][j + 1].rgbtRed * -1 +
                        copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 0 +
                        copy[i + 1][j].rgbtRed * 2 + copy[i + 1][j + 1].rgbtRed * 1;
            }
            else if (j == width - 1)
            {
                Gx[0] = copy[i - 1][j - 1].rgbtBlue * -1 + copy[i - 1][j].rgbtBlue * 0 +
                        copy[i][j - 1].rgbtBlue * -2 + copy[i][j].rgbtBlue * 0 +
                        copy[i + 1][j - 1].rgbtBlue * -1 + copy[i + 1][j].rgbtBlue * 0;
                Gy[0] = copy[i - 1][j - 1].rgbtBlue * -1 + copy[i - 1][j].rgbtBlue * -2 +
                        copy[i][j - 1].rgbtBlue * 0 + copy[i][j].rgbtBlue * 0 +
                        copy[i + 1][j - 1].rgbtBlue * 1 + copy[i + 1][j].rgbtBlue * 2;
                Gx[1] = copy[i - 1][j - 1].rgbtGreen * -1 + copy[i - 1][j].rgbtGreen * 0 +
                        copy[i][j - 1].rgbtGreen * -2 + copy[i][j].rgbtGreen * 0 +
                        copy[i + 1][j - 1].rgbtGreen * -1 + copy[i + 1][j].rgbtGreen * 0;
                Gy[1] = copy[i - 1][j - 1].rgbtGreen * -1 + copy[i - 1][j].rgbtGreen * -2 +
                        copy[i][j - 1].rgbtGreen * 0 + copy[i][j].rgbtGreen * 0 +
                        copy[i + 1][j - 1].rgbtGreen * 1 + copy[i + 1][j].rgbtGreen * 2;
                Gx[2] = copy[i - 1][j - 1].rgbtRed * -1 + copy[i - 1][j].rgbtRed * 0 +
                        copy[i][j - 1].rgbtRed * -2 + copy[i][j].rgbtRed * 0 +
                        copy[i + 1][j - 1].rgbtRed * -1 + copy[i + 1][j].rgbtRed * 0;
                Gy[2] = copy[i - 1][j - 1].rgbtRed * -1 + copy[i - 1][j].rgbtRed * -2 +
                        copy[i][j - 1].rgbtRed * 0 + copy[i][j].rgbtRed * 0 +
                        copy[i + 1][j - 1].rgbtRed * 1 + copy[i + 1][j].rgbtRed * 2;
            }
            else
            {
                Gx[0] = copy[i - 1][j - 1].rgbtBlue * -1 + copy[i - 1][j].rgbtBlue * 0 +
                        copy[i - 1][j + 1].rgbtBlue * 1 + copy[i][j - 1].rgbtBlue * -2 +
                        copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 2 +
                        copy[i + 1][j - 1].rgbtBlue * -1 + copy[i + 1][j].rgbtBlue * 0 +
                        copy[i + 1][j + 1].rgbtBlue * 1;
                Gy[0] = copy[i - 1][j - 1].rgbtBlue * -1 + copy[i - 1][j].rgbtBlue * -2 +
                        copy[i - 1][j + 1].rgbtBlue * -1 + copy[i][j - 1].rgbtBlue * 0 +
                        copy[i][j].rgbtBlue * 0 + copy[i][j + 1].rgbtBlue * 0 +
                        copy[i + 1][j - 1].rgbtBlue * 1 + copy[i + 1][j].rgbtBlue * 2 +
                        copy[i + 1][j + 1].rgbtBlue * 1;
                Gx[1] = copy[i - 1][j - 1].rgbtGreen * -1 + copy[i - 1][j].rgbtGreen * 0 +
                        copy[i - 1][j + 1].rgbtGreen * 1 + copy[i][j - 1].rgbtGreen * -2 +
                        copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 2 +
                        copy[i + 1][j - 1].rgbtGreen * -1 + copy[i + 1][j].rgbtGreen * 0 +
                        copy[i + 1][j + 1].rgbtGreen * 1;
                Gy[1] = copy[i - 1][j - 1].rgbtGreen * -1 + copy[i - 1][j].rgbtGreen * -2 +
                        copy[i - 1][j + 1].rgbtGreen * -1 + copy[i][j - 1].rgbtGreen * 0 +
                        copy[i][j].rgbtGreen * 0 + copy[i][j + 1].rgbtGreen * 0 +
                        copy[i + 1][j - 1].rgbtGreen * 1 + copy[i + 1][j].rgbtGreen * 2 +
                        copy[i + 1][j + 1].rgbtGreen * 1;
                Gx[2] = copy[i - 1][j - 1].rgbtRed * -1 + copy[i - 1][j].rgbtRed * 0 +
                        copy[i - 1][j + 1].rgbtRed * 1 + copy[i][j - 1].rgbtRed * -2 +
                        copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 2 +
                        copy[i + 1][j - 1].rgbtRed * -1 + copy[i + 1][j].rgbtRed * 0 +
                        copy[i + 1][j + 1].rgbtRed * 1;
                Gy[2] = copy[i - 1][j - 1].rgbtRed * -1 + copy[i - 1][j].rgbtRed * -2 +
                        copy[i - 1][j + 1].rgbtRed * -1 + copy[i][j - 1].rgbtRed * 0 +
                        copy[i][j].rgbtRed * 0 + copy[i][j + 1].rgbtRed * 0 +
                        copy[i + 1][j - 1].rgbtRed * 1 + copy[i + 1][j].rgbtRed * 2 +
                        copy[i + 1][j + 1].rgbtRed * 1;
            }

            G[0] = (int) round(sqrt(Gx[0] * Gx[0] + Gy[0] * Gy[0]));
            G[1] = (int) round(sqrt(Gx[1] * Gx[1] + Gy[1] * Gy[1]));
            G[2] = (int) round(sqrt(Gx[2] * Gx[2] + Gy[2] * Gy[2]));

            if (G[0] > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = G[0];
            }

            if (G[1] > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = G[1];
            }

            if (G[2] > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = G[2];
            }
        }
    }
    return;
}
