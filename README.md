# Metric Small Cancelation

Experimental estimate of the probability of metric small cancelation for group presentations.

## Requirements

To compile and run the code under `./cpp` which generates the experimental data:
 * `C++ 11`

To run the code under `./working` which plots the experimenal data:
 * `jupyter notebook` https://jupyter.org/
 * `SageMath` http://www.sagemath.org/
 * `sagemath-jupyter` SageMath Plugin for Jupyter Notebook

To generate the EPS figures under `./figures`:
 * `pdfcrop` (which is provided in TeXLive)
 * `pdftops` (which is provided in TeXLive)

## Generating Data

Execute the code under `./cpp` from within a directory of the form `./data/dirname`.
For example, one could run the following code
```sh
# create a new directory from the current time
DIR="./data/$(($(date +%s%N)/1000000))"
mkdir -p "$DIR"
cd "$DIR"
# execure the code to generate the output data within this directory
../../cpp/small_cancelation
```

## Generating Graphs

After generating a sufficient amount of data, open and run the SageMath notebook provided in `./working` with Jupyter Notebook. This code will output 9 PDF plots under `./output`. To then crop these graphs and convert them to the eps format run the `generate-figures.sh` script.

## License

Copyright (c) 2019 Alex Bishop  
Licensed under the MIT license.
