#include <stdio.h>
#include <stdlib.h>
#include <libcgroup.h>

int main()
{
    struct cgroup *cgroup;
    struct cgroup_controller *cpu_controller;
    struct cgroup_controller *memory_controller;
    int ret;

    // Initialize libcgroup
    ret = cgroup_init();
    if (ret)
    {
        fprintf(stderr, "Failed to initialize libcgroup: %s\n", cgroup_strerror(ret));
        return EXIT_FAILURE;
    }

    // Create a new cgroup
    cgroup = cgroup_new_cgroup("my_cgroup");
    if (!cgroup)
    {
        fprintf(stderr, "Failed to create cgroup\n");
        return EXIT_FAILURE;
    }

    // Add the CPU controller
    cpu_controller = cgroup_add_controller(cgroup, "cpu");
    if (!cpu_controller)
    {
        fprintf(stderr, "Failed to add CPU controller\n");
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    // Set CPU shares
    ret = cgroup_set_value_uint64(cpu_controller, "cpu.shares", 512);
    if (ret)
    {
        fprintf(stderr, "Failed to set CPU shares: %s\n", cgroup_strerror(ret));
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    // Add the Memory controller
    memory_controller = cgroup_add_controller(cgroup, "memory");
    if (!memory_controller)
    {
        fprintf(stderr, "Failed to add Memory controller\n");
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    // Set memory limit
    ret = cgroup_set_value_uint64(memory_controller, "memory.limit_in_bytes", 104857600); // 100MB
    if (ret)
    {
        fprintf(stderr, "Failed to set memory limit: %s\n", cgroup_strerror(ret));
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    // Create the cgroup in the kernel
    ret = cgroup_create_cgroup(cgroup, 0);
    if (ret)
    {
        fprintf(stderr, "Failed to create cgroup in the kernel: %s\n", cgroup_strerror(ret));
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    // Attach the current process to the cgroup
    ret = cgroup_attach_task(cgroup);
    if (ret)
    {
        fprintf(stderr, "Failed to attach task to cgroup: %s\n", cgroup_strerror(ret));
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    printf("Cgroup created and task attached successfully.\n");

    // Clean up
    cgroup_free(&cgroup);

    return EXIT_SUCCESS;
}