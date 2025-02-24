# RGA Analysis


## Compile:

Run the function `mbgr` or `mb` after loading the gemc/dev3 module. 
It will have the root pkgconfig files in the right place because 
they're installed by gemc/src.


## Run analysis code

### Interactive:

```
root  'rga_analysis.C("/opt/data/rga", true)'
```

### Batch and print all plots:

```
root -l -q 'rga_analysis.C(/opt/data/rga", true)'
```