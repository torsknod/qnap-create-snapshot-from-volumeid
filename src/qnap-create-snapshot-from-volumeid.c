#include <config.h>

#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif

#ifdef HAVE_ARGP_H
#include <argp.h>
#endif

#ifdef HAVE_ERRNO_H
#include <errno.h>
#endif

#ifdef HAVE_STRING_H
#include <string.h>
#endif

// Function prototype(s) for libuLinux_Storage
#ifdef HAVE_SNAPSHOT_CREATE
// TODO TK: Find out what argument b and c is used for
extern int Snapshot_Create(unsigned char *snapshot_id, unsigned char *b, int c);
#endif

#ifdef HAVE_NAS_SNAPSHOT_CREATE_BY_VOL
// FIXME TK: Find out what argument a is used for
extern int NAS_Snapshot_Create_By_Vol(unsigned char *a, int volume_id, unsigned char *snapshot_name, int *snapshot_id);
#endif

const char *argp_program_version = PACKAGE_STRING;
const char *argp_program_bug_address = PACKAGE_BUGREPORT;

struct arguments {
  unsigned char *snapshot_name;
  int volume_id;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
  struct arguments *arguments = state->input;

  switch (key) {
    case 's':
      if (strlen(arg) <= 0) {
        argp_usage(state);
      } else {
        arguments->snapshot_name = strdup(arg);
        if (arguments->snapshot_name == NULL) {
          argp_usage(state);
        }
      }
      break;
    case 'v':
      if (arg == NULL) {
        argp_usage(state);
      } else {
        char *endptr;
        unsigned long int uliArg;
        uliArg = strtoul(arg, &endptr, 10);
        if (arg != NULL && arg[0] != '\0' && endptr != NULL && endptr[0] == '\0' && uliArg > 0 && uliArg <= INT_MAX && errno == 0) {
          arguments->volume_id = uliArg;
        } else {
          argp_usage(state);
        }
      }
      break;
    case ARGP_KEY_ARG:
      // No arguments to parse
      break;
    case ARGP_KEY_END:
      // No arguments to parse
      break;
    default:
      return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  const static struct argp_option options[] = {
     { "snapshot", 's', "SNAPSHOT", 0, "Name of the snapshot to be created" },
     { "snapshot-name", 's', "SNAPSHOT_NAME", OPTION_ALIAS, "Name of the snapshot to be created" },
     { "volume",   'v', "VOLUME", 0, "Volume identifier (number code which can be found in /etc/volumes.conf)" },
     { "volume-id",   'v', "VOLUME-ID", OPTION_ALIAS, "Volume identifier (number code which can be found in /etc/volumes.conf)" },
     { NULL },
    };
  const static struct argp argp = {
    options: options,
    parser: parse_opt,
    args_doc: 0,
    doc: "Das ist ein Test",
    children: NULL,
    help_filter: NULL,
    argp_domain: NULL
  };
  int snapshot_id = -1;
  int result = -1;
  struct arguments arguments = {
    snapshot_name : NULL,
    volume_id : -1
  };

  argp_parse(&argp, argc, argv, 0, 0, &arguments);
  if (arguments.volume_id > 0) {
    printf("Volume ID: %i\n", arguments.volume_id);
  } else {
    printf("No Volume ID given!\n");
  }
  if (arguments.snapshot_name != NULL) {
    printf("Snapshot Name: %s\n", arguments.snapshot_name);
  } else {
    printf("No Snapshot Name given!\n");
  }
  if (arguments.volume_id > 0 && arguments.snapshot_name != NULL && strlen(arguments.snapshot_name) > 0) {
    result = NAS_Snapshot_Create_By_Vol(NULL, 3, arguments.snapshot_name, &snapshot_id);
    if (result > 0) {
      printf("ID of created Snapshot: %i\n", snapshot_id);
    }
    if (arguments.snapshot_name != NULL) {
      free(arguments.snapshot_name);
    }
    exit(result < 0 ? result : EXIT_SUCCESS);
  } else {
    if (arguments.snapshot_name != NULL) {
      free(arguments.snapshot_name);
    }
    exit(EXIT_FAILURE);
  }
}
