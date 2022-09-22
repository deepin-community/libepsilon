/*
 * $Id: color.c,v 1.15 2010/02/05 23:50:22 simakov Exp $
 *
 * EPSILON - wavelet image compression library.
 * Copyright (C) 2006,2007,2010 Alexander Simakov, <xander@entropyware.info>
 *
 * This file is part of EPSILON
 *
 * EPSILON is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EPSILON is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with EPSILON.  If not, see <http://www.gnu.org/licenses/>.
 *
 * http://epsilon-project.sourceforge.net
 */

#include <common.h>
#include <color.h>

/* Look-up tables for increase RGB to YCbCr conversion speed */

local double O_299000[256] = {
           0,    0.299,    0.598,    0.897,    1.196,    1.495,    1.794,    2.093,
       2.392,    2.691,     2.99,    3.289,    3.588,    3.887,    4.186,    4.485,
       4.784,    5.083,    5.382,    5.681,     5.98,    6.279,    6.578,    6.877,
       7.176,    7.475,    7.774,    8.073,    8.372,    8.671,     8.97,    9.269,
       9.568,    9.867,   10.166,   10.465,   10.764,   11.063,   11.362,   11.661,
       11.96,   12.259,   12.558,   12.857,   13.156,   13.455,   13.754,   14.053,
      14.352,   14.651,    14.95,   15.249,   15.548,   15.847,   16.146,   16.445,
      16.744,   17.043,   17.342,   17.641,    17.94,   18.239,   18.538,   18.837,
      19.136,   19.435,   19.734,   20.033,   20.332,   20.631,    20.93,   21.229,
      21.528,   21.827,   22.126,   22.425,   22.724,   23.023,   23.322,   23.621,
       23.92,   24.219,   24.518,   24.817,   25.116,   25.415,   25.714,   26.013,
      26.312,   26.611,    26.91,   27.209,   27.508,   27.807,   28.106,   28.405,
      28.704,   29.003,   29.302,   29.601,     29.9,   30.199,   30.498,   30.797,
      31.096,   31.395,   31.694,   31.993,   32.292,   32.591,    32.89,   33.189,
      33.488,   33.787,   34.086,   34.385,   34.684,   34.983,   35.282,   35.581,
       35.88,   36.179,   36.478,   36.777,   37.076,   37.375,   37.674,   37.973,
      38.272,   38.571,    38.87,   39.169,   39.468,   39.767,   40.066,   40.365,
      40.664,   40.963,   41.262,   41.561,    41.86,   42.159,   42.458,   42.757,
      43.056,   43.355,   43.654,   43.953,   44.252,   44.551,    44.85,   45.149,
      45.448,   45.747,   46.046,   46.345,   46.644,   46.943,   47.242,   47.541,
       47.84,   48.139,   48.438,   48.737,   49.036,   49.335,   49.634,   49.933,
      50.232,   50.531,    50.83,   51.129,   51.428,   51.727,   52.026,   52.325,
      52.624,   52.923,   53.222,   53.521,    53.82,   54.119,   54.418,   54.717,
      55.016,   55.315,   55.614,   55.913,   56.212,   56.511,    56.81,   57.109,
      57.408,   57.707,   58.006,   58.305,   58.604,   58.903,   59.202,   59.501,
        59.8,   60.099,   60.398,   60.697,   60.996,   61.295,   61.594,   61.893,
      62.192,   62.491,    62.79,   63.089,   63.388,   63.687,   63.986,   64.285,
      64.584,   64.883,   65.182,   65.481,    65.78,   66.079,   66.378,   66.677,
      66.976,   67.275,   67.574,   67.873,   68.172,   68.471,    68.77,   69.069,
      69.368,   69.667,   69.966,   70.265,   70.564,   70.863,   71.162,   71.461,
       71.76,   72.059,   72.358,   72.657,   72.956,   73.255,   73.554,   73.853,
      74.152,   74.451,    74.75,   75.049,   75.348,   75.647,   75.946,   76.245,
};

local double O_587000[256] = {
           0,    0.587,    1.174,    1.761,    2.348,    2.935,    3.522,    4.109,
       4.696,    5.283,     5.87,    6.457,    7.044,    7.631,    8.218,    8.805,
       9.392,    9.979,   10.566,   11.153,    11.74,   12.327,   12.914,   13.501,
      14.088,   14.675,   15.262,   15.849,   16.436,   17.023,    17.61,   18.197,
      18.784,   19.371,   19.958,   20.545,   21.132,   21.719,   22.306,   22.893,
       23.48,   24.067,   24.654,   25.241,   25.828,   26.415,   27.002,   27.589,
      28.176,   28.763,    29.35,   29.937,   30.524,   31.111,   31.698,   32.285,
      32.872,   33.459,   34.046,   34.633,    35.22,   35.807,   36.394,   36.981,
      37.568,   38.155,   38.742,   39.329,   39.916,   40.503,    41.09,   41.677,
      42.264,   42.851,   43.438,   44.025,   44.612,   45.199,   45.786,   46.373,
       46.96,   47.547,   48.134,   48.721,   49.308,   49.895,   50.482,   51.069,
      51.656,   52.243,    52.83,   53.417,   54.004,   54.591,   55.178,   55.765,
      56.352,   56.939,   57.526,   58.113,     58.7,   59.287,   59.874,   60.461,
      61.048,   61.635,   62.222,   62.809,   63.396,   63.983,    64.57,   65.157,
      65.744,   66.331,   66.918,   67.505,   68.092,   68.679,   69.266,   69.853,
       70.44,   71.027,   71.614,   72.201,   72.788,   73.375,   73.962,   74.549,
      75.136,   75.723,    76.31,   76.897,   77.484,   78.071,   78.658,   79.245,
      79.832,   80.419,   81.006,   81.593,    82.18,   82.767,   83.354,   83.941,
      84.528,   85.115,   85.702,   86.289,   86.876,   87.463,    88.05,   88.637,
      89.224,   89.811,   90.398,   90.985,   91.572,   92.159,   92.746,   93.333,
       93.92,   94.507,   95.094,   95.681,   96.268,   96.855,   97.442,   98.029,
      98.616,   99.203,    99.79,  100.377,  100.964,  101.551,  102.138,  102.725,
     103.312,  103.899,  104.486,  105.073,   105.66,  106.247,  106.834,  107.421,
     108.008,  108.595,  109.182,  109.769,  110.356,  110.943,   111.53,  112.117,
     112.704,  113.291,  113.878,  114.465,  115.052,  115.639,  116.226,  116.813,
       117.4,  117.987,  118.574,  119.161,  119.748,  120.335,  120.922,  121.509,
     122.096,  122.683,   123.27,  123.857,  124.444,  125.031,  125.618,  126.205,
     126.792,  127.379,  127.966,  128.553,   129.14,  129.727,  130.314,  130.901,
     131.488,  132.075,  132.662,  133.249,  133.836,  134.423,   135.01,  135.597,
     136.184,  136.771,  137.358,  137.945,  138.532,  139.119,  139.706,  140.293,
      140.88,  141.467,  142.054,  142.641,  143.228,  143.815,  144.402,  144.989,
     145.576,  146.163,   146.75,  147.337,  147.924,  148.511,  149.098,  149.685,
};

local double O_114000[256] = {
           0,    0.114,    0.228,    0.342,    0.456,     0.57,    0.684,    0.798,
       0.912,    1.026,     1.14,    1.254,    1.368,    1.482,    1.596,     1.71,
       1.824,    1.938,    2.052,    2.166,     2.28,    2.394,    2.508,    2.622,
       2.736,     2.85,    2.964,    3.078,    3.192,    3.306,     3.42,    3.534,
       3.648,    3.762,    3.876,     3.99,    4.104,    4.218,    4.332,    4.446,
        4.56,    4.674,    4.788,    4.902,    5.016,     5.13,    5.244,    5.358,
       5.472,    5.586,      5.7,    5.814,    5.928,    6.042,    6.156,     6.27,
       6.384,    6.498,    6.612,    6.726,     6.84,    6.954,    7.068,    7.182,
       7.296,     7.41,    7.524,    7.638,    7.752,    7.866,     7.98,    8.094,
       8.208,    8.322,    8.436,     8.55,    8.664,    8.778,    8.892,    9.006,
        9.12,    9.234,    9.348,    9.462,    9.576,     9.69,    9.804,    9.918,
      10.032,   10.146,    10.26,   10.374,   10.488,   10.602,   10.716,    10.83,
      10.944,   11.058,   11.172,   11.286,     11.4,   11.514,   11.628,   11.742,
      11.856,    11.97,   12.084,   12.198,   12.312,   12.426,    12.54,   12.654,
      12.768,   12.882,   12.996,    13.11,   13.224,   13.338,   13.452,   13.566,
       13.68,   13.794,   13.908,   14.022,   14.136,    14.25,   14.364,   14.478,
      14.592,   14.706,    14.82,   14.934,   15.048,   15.162,   15.276,    15.39,
      15.504,   15.618,   15.732,   15.846,    15.96,   16.074,   16.188,   16.302,
      16.416,    16.53,   16.644,   16.758,   16.872,   16.986,     17.1,   17.214,
      17.328,   17.442,   17.556,    17.67,   17.784,   17.898,   18.012,   18.126,
       18.24,   18.354,   18.468,   18.582,   18.696,    18.81,   18.924,   19.038,
      19.152,   19.266,    19.38,   19.494,   19.608,   19.722,   19.836,    19.95,
      20.064,   20.178,   20.292,   20.406,    20.52,   20.634,   20.748,   20.862,
      20.976,    21.09,   21.204,   21.318,   21.432,   21.546,    21.66,   21.774,
      21.888,   22.002,   22.116,    22.23,   22.344,   22.458,   22.572,   22.686,
        22.8,   22.914,   23.028,   23.142,   23.256,    23.37,   23.484,   23.598,
      23.712,   23.826,    23.94,   24.054,   24.168,   24.282,   24.396,    24.51,
      24.624,   24.738,   24.852,   24.966,    25.08,   25.194,   25.308,   25.422,
      25.536,    25.65,   25.764,   25.878,   25.992,   26.106,    26.22,   26.334,
      26.448,   26.562,   26.676,    26.79,   26.904,   27.018,   27.132,   27.246,
       27.36,   27.474,   27.588,   27.702,   27.816,    27.93,   28.044,   28.158,
      28.272,   28.386,     28.5,   28.614,   28.728,   28.842,   28.956,    29.07,
};

local double O_168736[256] = {
           0, 0.168736, 0.337472, 0.506208, 0.674944,  0.84368,  1.01242,  1.18115,
     1.34989,  1.51862,  1.68736,   1.8561,  2.02483,  2.19357,   2.3623,  2.53104,
     2.69978,  2.86851,  3.03725,  3.20598,  3.37472,  3.54346,  3.71219,  3.88093,
     4.04966,   4.2184,  4.38714,  4.55587,  4.72461,  4.89334,  5.06208,  5.23082,
     5.39955,  5.56829,  5.73702,  5.90576,   6.0745,  6.24323,  6.41197,   6.5807,
     6.74944,  6.91818,  7.08691,  7.25565,  7.42438,  7.59312,  7.76186,  7.93059,
     8.09933,  8.26806,   8.4368,  8.60554,  8.77427,  8.94301,  9.11174,  9.28048,
     9.44922,  9.61795,  9.78669,  9.95542,  10.1242,  10.2929,  10.4616,  10.6304,
     10.7991,  10.9678,  11.1366,  11.3053,   11.474,  11.6428,  11.8115,  11.9803,
      12.149,  12.3177,  12.4865,  12.6552,  12.8239,  12.9927,  13.1614,  13.3301,
     13.4989,  13.6676,  13.8364,  14.0051,  14.1738,  14.3426,  14.5113,    14.68,
     14.8488,  15.0175,  15.1862,   15.355,  15.5237,  15.6924,  15.8612,  16.0299,
     16.1987,  16.3674,  16.5361,  16.7049,  16.8736,  17.0423,  17.2111,  17.3798,
     17.5485,  17.7173,   17.886,  18.0548,  18.2235,  18.3922,   18.561,  18.7297,
     18.8984,  19.0672,  19.2359,  19.4046,  19.5734,  19.7421,  19.9108,  20.0796,
     20.2483,  20.4171,  20.5858,  20.7545,  20.9233,   21.092,  21.2607,  21.4295,
     21.5982,  21.7669,  21.9357,  22.1044,  22.2732,  22.4419,  22.6106,  22.7794,
     22.9481,  23.1168,  23.2856,  23.4543,   23.623,  23.7918,  23.9605,  24.1292,
      24.298,  24.4667,  24.6355,  24.8042,  24.9729,  25.1417,  25.3104,  25.4791,
     25.6479,  25.8166,  25.9853,  26.1541,  26.3228,  26.4916,  26.6603,   26.829,
     26.9978,  27.1665,  27.3352,   27.504,  27.6727,  27.8414,  28.0102,  28.1789,
     28.3476,  28.5164,  28.6851,  28.8539,  29.0226,  29.1913,  29.3601,  29.5288,
     29.6975,  29.8663,   30.035,  30.2037,  30.3725,  30.5412,    30.71,  30.8787,
     31.0474,  31.2162,  31.3849,  31.5536,  31.7224,  31.8911,  32.0598,  32.2286,
     32.3973,   32.566,  32.7348,  32.9035,  33.0723,   33.241,  33.4097,  33.5785,
     33.7472,  33.9159,  34.0847,  34.2534,  34.4221,  34.5909,  34.7596,  34.9284,
     35.0971,  35.2658,  35.4346,  35.6033,   35.772,  35.9408,  36.1095,  36.2782,
      36.447,  36.6157,  36.7844,  36.9532,  37.1219,  37.2907,  37.4594,  37.6281,
     37.7969,  37.9656,  38.1343,  38.3031,  38.4718,  38.6405,  38.8093,   38.978,
     39.1468,  39.3155,  39.4842,   39.653,  39.8217,  39.9904,  40.1592,  40.3279,
     40.4966,  40.6654,  40.8341,  41.0028,  41.1716,  41.3403,  41.5091,  41.6778,
     41.8465,  42.0153,   42.184,  42.3527,  42.5215,  42.6902,  42.8589,  43.0277,
};

local double O_331264[256] = {
           0, 0.331264, 0.662528, 0.993792,  1.32506,  1.65632,  1.98758,  2.31885,
     2.65011,  2.98138,  3.31264,   3.6439,  3.97517,  4.30643,   4.6377,  4.96896,
     5.30022,  5.63149,  5.96275,  6.29402,  6.62528,  6.95654,  7.28781,  7.61907,
     7.95034,   8.2816,  8.61286,  8.94413,  9.27539,  9.60666,  9.93792,  10.2692,
     10.6004,  10.9317,   11.263,  11.5942,  11.9255,  12.2568,   12.588,  12.9193,
     13.2506,  13.5818,  13.9131,  14.2444,  14.5756,  14.9069,  15.2381,  15.5694,
     15.9007,  16.2319,  16.5632,  16.8945,  17.2257,   17.557,  17.8883,  18.2195,
     18.5508,   18.882,  19.2133,  19.5446,  19.8758,  20.2071,  20.5384,  20.8696,
     21.2009,  21.5322,  21.8634,  22.1947,   22.526,  22.8572,  23.1885,  23.5197,
      23.851,  24.1823,  24.5135,  24.8448,  25.1761,  25.5073,  25.8386,  26.1699,
     26.5011,  26.8324,  27.1636,  27.4949,  27.8262,  28.1574,  28.4887,    28.82,
     29.1512,  29.4825,  29.8138,   30.145,  30.4763,  30.8076,  31.1388,  31.4701,
     31.8013,  32.1326,  32.4639,  32.7951,  33.1264,  33.4577,  33.7889,  34.1202,
     34.4515,  34.7827,   35.114,  35.4452,  35.7765,  36.1078,   36.439,  36.7703,
     37.1016,  37.4328,  37.7641,  38.0954,  38.4266,  38.7579,  39.0892,  39.4204,
     39.7517,  40.0829,  40.4142,  40.7455,  41.0767,   41.408,  41.7393,  42.0705,
     42.4018,  42.7331,  43.0643,  43.3956,  43.7268,  44.0581,  44.3894,  44.7206,
     45.0519,  45.3832,  45.7144,  46.0457,   46.377,  46.7082,  47.0395,  47.3708,
      47.702,  48.0333,  48.3645,  48.6958,  49.0271,  49.3583,  49.6896,  50.0209,
     50.3521,  50.6834,  51.0147,  51.3459,  51.6772,  52.0084,  52.3397,   52.671,
     53.0022,  53.3335,  53.6648,   53.996,  54.3273,  54.6586,  54.9898,  55.3211,
     55.6524,  55.9836,  56.3149,  56.6461,  56.9774,  57.3087,  57.6399,  57.9712,
     58.3025,  58.6337,   58.965,  59.2963,  59.6275,  59.9588,    60.29,  60.6213,
     60.9526,  61.2838,  61.6151,  61.9464,  62.2776,  62.6089,  62.9402,  63.2714,
     63.6027,   63.934,  64.2652,  64.5965,  64.9277,   65.259,  65.5903,  65.9215,
     66.2528,  66.5841,  66.9153,  67.2466,  67.5779,  67.9091,  68.2404,  68.5716,
     68.9029,  69.2342,  69.5654,  69.8967,   70.228,  70.5592,  70.8905,  71.2218,
      71.553,  71.8843,  72.2156,  72.5468,  72.8781,  73.2093,  73.5406,  73.8719,
     74.2031,  74.5344,  74.8657,  75.1969,  75.5282,  75.8595,  76.1907,   76.522,
     76.8532,  77.1845,  77.5158,   77.847,  78.1783,  78.5096,  78.8408,  79.1721,
     79.5034,  79.8346,  80.1659,  80.4972,  80.8284,  81.1597,  81.4909,  81.8222,
     82.1535,  82.4847,   82.816,  83.1473,  83.4785,  83.8098,  84.1411,  84.4723,
};

local double O_500000[256] = {
           0,      0.5,        1,      1.5,        2,      2.5,        3,      3.5,
           4,      4.5,        5,      5.5,        6,      6.5,        7,      7.5,
           8,      8.5,        9,      9.5,       10,     10.5,       11,     11.5,
          12,     12.5,       13,     13.5,       14,     14.5,       15,     15.5,
          16,     16.5,       17,     17.5,       18,     18.5,       19,     19.5,
          20,     20.5,       21,     21.5,       22,     22.5,       23,     23.5,
          24,     24.5,       25,     25.5,       26,     26.5,       27,     27.5,
          28,     28.5,       29,     29.5,       30,     30.5,       31,     31.5,
          32,     32.5,       33,     33.5,       34,     34.5,       35,     35.5,
          36,     36.5,       37,     37.5,       38,     38.5,       39,     39.5,
          40,     40.5,       41,     41.5,       42,     42.5,       43,     43.5,
          44,     44.5,       45,     45.5,       46,     46.5,       47,     47.5,
          48,     48.5,       49,     49.5,       50,     50.5,       51,     51.5,
          52,     52.5,       53,     53.5,       54,     54.5,       55,     55.5,
          56,     56.5,       57,     57.5,       58,     58.5,       59,     59.5,
          60,     60.5,       61,     61.5,       62,     62.5,       63,     63.5,
          64,     64.5,       65,     65.5,       66,     66.5,       67,     67.5,
          68,     68.5,       69,     69.5,       70,     70.5,       71,     71.5,
          72,     72.5,       73,     73.5,       74,     74.5,       75,     75.5,
          76,     76.5,       77,     77.5,       78,     78.5,       79,     79.5,
          80,     80.5,       81,     81.5,       82,     82.5,       83,     83.5,
          84,     84.5,       85,     85.5,       86,     86.5,       87,     87.5,
          88,     88.5,       89,     89.5,       90,     90.5,       91,     91.5,
          92,     92.5,       93,     93.5,       94,     94.5,       95,     95.5,
          96,     96.5,       97,     97.5,       98,     98.5,       99,     99.5,
         100,    100.5,      101,    101.5,      102,    102.5,      103,    103.5,
         104,    104.5,      105,    105.5,      106,    106.5,      107,    107.5,
         108,    108.5,      109,    109.5,      110,    110.5,      111,    111.5,
         112,    112.5,      113,    113.5,      114,    114.5,      115,    115.5,
         116,    116.5,      117,    117.5,      118,    118.5,      119,    119.5,
         120,    120.5,      121,    121.5,      122,    122.5,      123,    123.5,
         124,    124.5,      125,    125.5,      126,    126.5,      127,    127.5,
};

local double O_418688[256] = {
           0, 0.418688, 0.837376,  1.25606,  1.67475,  2.09344,  2.51213,  2.93082,
      3.3495,  3.76819,  4.18688,  4.60557,  5.02426,  5.44294,  5.86163,  6.28032,
     6.69901,   7.1177,  7.53638,  7.95507,  8.37376,  8.79245,  9.21114,  9.62982,
     10.0485,  10.4672,  10.8859,  11.3046,  11.7233,   12.142,  12.5606,  12.9793,
      13.398,  13.8167,  14.2354,  14.6541,  15.0728,  15.4915,  15.9101,  16.3288,
     16.7475,  17.1662,  17.5849,  18.0036,  18.4223,   18.841,  19.2596,  19.6783,
      20.097,  20.5157,  20.9344,  21.3531,  21.7718,  22.1905,  22.6092,  23.0278,
     23.4465,  23.8652,  24.2839,  24.7026,  25.1213,    25.54,  25.9587,  26.3773,
      26.796,  27.2147,  27.6334,  28.0521,  28.4708,  28.8895,  29.3082,  29.7268,
     30.1455,  30.5642,  30.9829,  31.4016,  31.8203,   32.239,  32.6577,  33.0764,
      33.495,  33.9137,  34.3324,  34.7511,  35.1698,  35.5885,  36.0072,  36.4259,
     36.8445,  37.2632,  37.6819,  38.1006,  38.5193,   38.938,  39.3567,  39.7754,
      40.194,  40.6127,  41.0314,  41.4501,  41.8688,  42.2875,  42.7062,  43.1249,
     43.5436,  43.9622,  44.3809,  44.7996,  45.2183,   45.637,  46.0557,  46.4744,
     46.8931,  47.3117,  47.7304,  48.1491,  48.5678,  48.9865,  49.4052,  49.8239,
     50.2426,  50.6612,  51.0799,  51.4986,  51.9173,   52.336,  52.7547,  53.1734,
     53.5921,  54.0108,  54.4294,  54.8481,  55.2668,  55.6855,  56.1042,  56.5229,
     56.9416,  57.3603,  57.7789,  58.1976,  58.6163,   59.035,  59.4537,  59.8724,
     60.2911,  60.7098,  61.1284,  61.5471,  61.9658,  62.3845,  62.8032,  63.2219,
     63.6406,  64.0593,   64.478,  64.8966,  65.3153,   65.734,  66.1527,  66.5714,
     66.9901,  67.4088,  67.8275,  68.2461,  68.6648,  69.0835,  69.5022,  69.9209,
     70.3396,  70.7583,   71.177,  71.5956,  72.0143,   72.433,  72.8517,  73.2704,
     73.6891,  74.1078,  74.5265,  74.9452,  75.3638,  75.7825,  76.2012,  76.6199,
     77.0386,  77.4573,   77.876,  78.2947,  78.7133,   79.132,  79.5507,  79.9694,
     80.3881,  80.8068,  81.2255,  81.6442,  82.0628,  82.4815,  82.9002,  83.3189,
     83.7376,  84.1563,   84.575,  84.9937,  85.4124,   85.831,  86.2497,  86.6684,
     87.0871,  87.5058,  87.9245,  88.3432,  88.7619,  89.1805,  89.5992,  90.0179,
     90.4366,  90.8553,   91.274,  91.6927,  92.1114,    92.53,  92.9487,  93.3674,
     93.7861,  94.2048,  94.6235,  95.0422,  95.4609,  95.8796,  96.2982,  96.7169,
     97.1356,  97.5543,   97.973,  98.3917,  98.8104,  99.2291,  99.6477,  100.066,
     100.485,  100.904,  101.322,  101.741,   102.16,  102.579,  102.997,  103.416,
     103.835,  104.253,  104.672,  105.091,  105.509,  105.928,  106.347,  106.765,
};

local double O_081312[256] = {
           0, 0.081312, 0.162624, 0.243936, 0.325248,  0.40656, 0.487872, 0.569184,
    0.650496, 0.731808,  0.81312, 0.894432, 0.975744,  1.05706,  1.13837,  1.21968,
     1.30099,   1.3823,  1.46362,  1.54493,  1.62624,  1.70755,  1.78886,  1.87018,
     1.95149,   2.0328,  2.11411,  2.19542,  2.27674,  2.35805,  2.43936,  2.52067,
     2.60198,   2.6833,  2.76461,  2.84592,  2.92723,  3.00854,  3.08986,  3.17117,
     3.25248,  3.33379,   3.4151,  3.49642,  3.57773,  3.65904,  3.74035,  3.82166,
     3.90298,  3.98429,   4.0656,  4.14691,  4.22822,  4.30954,  4.39085,  4.47216,
     4.55347,  4.63478,   4.7161,  4.79741,  4.87872,  4.96003,  5.04134,  5.12266,
     5.20397,  5.28528,  5.36659,   5.4479,  5.52922,  5.61053,  5.69184,  5.77315,
     5.85446,  5.93578,  6.01709,   6.0984,  6.17971,  6.26102,  6.34234,  6.42365,
     6.50496,  6.58627,  6.66758,   6.7489,  6.83021,  6.91152,  6.99283,  7.07414,
     7.15546,  7.23677,  7.31808,  7.39939,   7.4807,  7.56202,  7.64333,  7.72464,
     7.80595,  7.88726,  7.96858,  8.04989,   8.1312,  8.21251,  8.29382,  8.37514,
     8.45645,  8.53776,  8.61907,  8.70038,   8.7817,  8.86301,  8.94432,  9.02563,
     9.10694,  9.18826,  9.26957,  9.35088,  9.43219,   9.5135,  9.59482,  9.67613,
     9.75744,  9.83875,  9.92006,  10.0014,  10.0827,   10.164,  10.2453,  10.3266,
     10.4079,  10.4892,  10.5706,  10.6519,  10.7332,  10.8145,  10.8958,  10.9771,
     11.0584,  11.1397,  11.2211,  11.3024,  11.3837,   11.465,  11.5463,  11.6276,
     11.7089,  11.7902,  11.8716,  11.9529,  12.0342,  12.1155,  12.1968,  12.2781,
     12.3594,  12.4407,   12.522,  12.6034,  12.6847,   12.766,  12.8473,  12.9286,
     13.0099,  13.0912,  13.1725,  13.2539,  13.3352,  13.4165,  13.4978,  13.5791,
     13.6604,  13.7417,   13.823,  13.9044,  13.9857,   14.067,  14.1483,  14.2296,
     14.3109,  14.3922,  14.4735,  14.5548,  14.6362,  14.7175,  14.7988,  14.8801,
     14.9614,  15.0427,   15.124,  15.2053,  15.2867,   15.368,  15.4493,  15.5306,
     15.6119,  15.6932,  15.7745,  15.8558,  15.9372,  16.0185,  16.0998,  16.1811,
     16.2624,  16.3437,   16.425,  16.5063,  16.5876,   16.669,  16.7503,  16.8316,
     16.9129,  16.9942,  17.0755,  17.1568,  17.2381,  17.3195,  17.4008,  17.4821,
     17.5634,  17.6447,   17.726,  17.8073,  17.8886,    17.97,  18.0513,  18.1326,
     18.2139,  18.2952,  18.3765,  18.4578,  18.5391,  18.6204,  18.7018,  18.7831,
     18.8644,  18.9457,   19.027,  19.1083,  19.1896,  19.2709,  19.3523,  19.4336,
     19.5149,  19.5962,  19.6775,  19.7588,  19.8401,  19.9214,  20.0028,  20.0841,
     20.1654,  20.2467,   20.328,  20.4093,  20.4906,  20.5719,  20.6532,  20.7346,
};

void convert_RGB_to_YCbCr(coeff_t **R, coeff_t **G, coeff_t **B,
                          coeff_t **Y, coeff_t **Cb, coeff_t **Cr,
                          int width, int height)
{
    int i, j;

    assert(width > 0);
    assert(height > 0);

    /* Perhaps one should optimize this code with integer-valued
     * look-up tables. On the other hand, the rest of the program
     * (e.g. wavelet transform, resampling etc.) still using FPU.
     * Moreover, additional rounding operation (even with proper
     * rescaling) will involve some marginal image distortion. */
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            int r = (int) R[i][j];
            int g = (int) G[i][j];
            int b = (int) B[i][j];

            Y[i][j]  =  O_299000[r] + O_587000[g] + O_114000[b];
            Cb[i][j] = -O_168736[r] - O_331264[g] + O_500000[b] + 128.0;
            Cr[i][j] =  O_500000[r] - O_418688[g] - O_081312[b] + 128.0;
        }
    }
}

void convert_YCbCr_to_RGB(coeff_t **Y, coeff_t **Cb, coeff_t **Cr,
                          coeff_t **R, coeff_t **G, coeff_t **B,
                          int width, int height)
{
    int i, j;

    assert(width > 0);
    assert(height > 0);

    /* Due to rounding and quantization errors output RGB values
     * may not be enclosed within [0..255] interval. To solve
     * this problem the values are clipped after transformation. */
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            R[i][j] = CLIP(Y[i][j] + (Cr[i][j] - 128.0) * 1.402);
            G[i][j] = CLIP(Y[i][j] - (Cb[i][j] - 128.0) * 0.34413 - (Cr[i][j] - 128.0) * 0.71414);
            B[i][j] = CLIP(Y[i][j] + (Cb[i][j] - 128.0) * 1.772);
        }
    }
}

void clip_channel(coeff_t **channel, int width, int height)
{
    int i, j;

    assert(width > 0);
    assert(height > 0);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            channel[i][j] = CLIP(channel[i][j]);
        }
    }
}
