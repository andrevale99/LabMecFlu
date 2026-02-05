idf_component_register(SRCS "LabMecFlu.c"
                    INCLUDE_DIRS "include"
                    REQUIRES driver ads111x LabMecFluUART
                    LabMecFluPWM)
