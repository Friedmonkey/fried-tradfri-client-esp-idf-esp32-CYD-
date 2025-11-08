idf_component_register(
    SRCS "src/fried_tradfri_client.c"
    INCLUDE_DIRS "include"
    REQUIRES fried_coaps_client fdata
)
