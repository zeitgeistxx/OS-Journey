#include <stdio.h>
#include <stdlib.h>
#include <libcgroup.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#ifndef MEMORY_LIMIT_IN_GB
#define MEMORY_LIMIT_IN_GB 1
#endif

int main()
{
    struct cgroup *cgroup;
    struct cgroup_controller *cpu_controller;
    struct cgroup_controller *memory_controller;
    int ret;

    ret = cgroup_init();
    if (ret != 0)
    {
        fprintf(stderr, "Failed to initialize libcgroup: %s\n", cgroup_strerror(ret));
        return EXIT_FAILURE;
    }

    cgroup = cgroup_new_cgroup("capy");
    if (cgroup == NULL)
    {
        fprintf(stderr, "Failed to create cgroup: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    cpu_controller = cgroup_add_controller(cgroup, "cpu");
    if (cpu_controller == NULL)
    {
        fprintf(stderr, "Failed to add CPU controller: %s\n", strerror(errno));
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    ret = cgroup_set_value_uint64(cpu_controller, "cpu.shares", 512);
    if (ret != 0)
    {
        fprintf(stderr, "Failed to set CPU shares: %s\n", cgroup_strerror(ret));
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    memory_controller = cgroup_add_controller(cgroup, "memory");
    if (memory_controller == NULL)
    {
        fprintf(stderr, "Failed to add Memory controller: %s\n", strerror(errno));
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    ret = cgroup_set_value_uint64(memory_controller, "memory.limit_in_bytes", 100 * 1024 * 1024); // 100MB
    if (ret != 0)
    {
        fprintf(stderr, "Failed to set memory limit: %s\n", cgroup_strerror(ret));
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    // Create the cgroup in the kernel
    ret = cgroup_create_cgroup(cgroup, 0);
    if (ret != 0)
    {
        fprintf(stderr, "Failed to create cgroup in the kernel: %s\n", cgroup_strerror(ret));
        cgroup_free(&cgroup);
        return EXIT_FAILURE;
    }

    // Attach the current process to the cgroup
    // ret = cgroup_attach_task_pid(cgroup, getpid());
    // if (ret != 0)
    // {
    //     fprintf(stderr, "Failed to attach task to cgroup: %s\n", cgroup_strerror(ret));
    //     cgroup_free(&cgroup);
    //     return EXIT_FAILURE;
    // }

    // printf("Cgroup created and task attached successfully.\n");

    // Clean up
    cgroup_free(&cgroup);

    return EXIT_SUCCESS;
}
