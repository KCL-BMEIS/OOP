# Projects used on Object-Oriented Programming module

This repo holds project descriptions, data and solutions for the projects to be used for teaching on the [Object-Oriented Programming course](../).

## DNA shotgun sequencing
- [instructions](DNA_shotgun_sequencing/assignment.md)
- [data](DNA_shotgun_sequencing/data/)
- [solution](../../../tree/shotgun_sequencing_solution/projects/DNA_shotgun_sequencing/solution) (with [full history](../../../commits/shotgun_sequencing_solution/projects/DNA_shotgun_sequencing/solution))
 
## fMRI correlation analysis
- [instructions](fMRI/assignment.md)
- [data](fMRI/data/)
- [solution](../../../tree/fmri_solution/projects/fMRI/solution) (with [full history](../../../commits/fmri_solution/projects/fMRI/solution))

## Modular robot arm control
- [instructions](robot_arm/assignment.md)
- [data](robot_arm/data/)
- [solution](../../../tree/robot_solution/projects/robot_arm/solution) (with [full history](../../../commits/robot_solution/projects/robot_arm/solution))


# Keeping your code up to date

We have written a short script to simplify the process of keeping your
code up to date with the solutions as we progress through the course. 

This will download the solutions (and data if you request it) into the *current
folder*, with this file structure:
```
.
├── DNA_shotgun_sequencing
│   ├── data
│   └── solution
├── fMRI
│   ├── data
│   └── solution
└── robot_arm
    ├── data
    └── solution
```

## Updating your code to the latest version:

First, make sure to *change directory* using `cd` into a suitable location,
where you keep your own code. This will differ for different people, so please
use a folder that works for you. For example:
```
cd Documents/OOP
```

Once you are in the right folder, copy & paste the following into your terminal:
```
curl -s https://raw.githubusercontent.com/KCL-BMEIS/OOP/refs/heads/main/projects/update_solution | bash
```

### Updating the data to the latest version:

Make sure you are in the right folder (see above), then copy & paste the following into your terminal:
```
curl -s https://raw.githubusercontent.com/KCL-BMEIS/OOP/refs/heads/main/projects/update_solution | bash -s -- data
```



