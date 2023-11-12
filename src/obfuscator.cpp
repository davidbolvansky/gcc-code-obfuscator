#include <gcc-plugin.h>
#include <plugin-version.h>

#include <tree.h>
#include <tree-pass.h>
#include <context.h>
#include <stringpool.h>
#include <attribs.h>

int plugin_is_GPL_compatible;

static struct attribute_spec noobfuscate_attr =
{
    .name = "noobfuscate",
    .min_length = 0,
    .max_length = 0,
    .decl_required = true,
    .type_required = false,
    .function_type_required = false,
    .handler = NULL,
};

static bool has_noobfuscate_attr(function *fun) {
    tree attr = lookup_attribute("noobfuscate", DECL_ATTRIBUTES(fun->decl));
    return attr == NULL_TREE;
}

static unsigned int obfuscate(function *fun) {
    if (has_noobfuscate_attr(fun)) return 0;

    puts("Obfuscating function");
    // todo
    return 0;
}

static void register_attributes(void *event_data, void *data) {
    register_attribute(&noobfuscate_attr);
}

const pass_data obfuscator_pass_data = {
    .type = GIMPLE_PASS,
    .name = "obfuscator",
    .optinfo_flags = OPTGROUP_NONE,
    .tv_id = TV_NONE,
    .properties_required = 0,
    .properties_provided = 0,
    .properties_destroyed = 0,
    .todo_flags_start = 0,
    .todo_flags_finish = 0,
};

class obfuscator_pass : public gimple_opt_pass {
public:
    obfuscator_pass(gcc::context *ctx)
        : gimple_opt_pass(obfuscator_pass_data, ctx) {}

    virtual unsigned int execute(function *fun) override {
        return obfuscate(fun);
    }

    virtual obfuscator_pass* clone() override {
        return new obfuscator_pass(g);
    }
};

int plugin_init(struct plugin_name_args *plugin_info, struct plugin_gcc_version *version) {
    if (!plugin_default_version_check(version, &gcc_version)) {
        return 1; // Version mismatch
    }

    // register_callback(plugin_info->base_name, PLUGIN_INFO, NULL, &obfuscator_plugin_info);
    register_callback(plugin_info->base_name, PLUGIN_ATTRIBUTES, register_attributes, NULL);

    struct register_pass_info pass_info;
    pass_info.pass = new obfuscator_pass(g);
    pass_info.reference_pass_name = "cfg";
    pass_info.ref_pass_instance_number = 1;
    pass_info.pos_op = PASS_POS_INSERT_AFTER;

    register_callback(plugin_info->base_name, PLUGIN_PASS_MANAGER_SETUP, NULL, &pass_info);

    return 0;
}
