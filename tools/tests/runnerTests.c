#include <cgreen/cgreen.h>

#ifdef __cplusplus
namespace cgreen {
#endif

#include "runner.c"

Describe(Runner);

BeforeEach(Runner){}

AfterEach(Runner){}

#define CONTEXT_NAME "context"
#define TEST_NAME "test"

static char FUNCTION_NAME[] = CGREEN_SPEC_PREFIX CGREEN_SEPARATOR CONTEXT_NAME CGREEN_SEPARATOR TEST_NAME;
static char FUNCTION_NAME_WITH_DEFAULT_CONTEXT[] = CGREEN_SPEC_PREFIX CGREEN_SEPARATOR CGREEN_DEFAULT_SUITE CGREEN_SEPARATOR TEST_NAME;

Ensure(Runner, can_get_suite_name_from_symbol) {
    assert_that(suite_name_of_symbol(FUNCTION_NAME), is_equal_to_string(CONTEXT_NAME));
}

Ensure(Runner, can_get_test_name_from_symbol) {
    assert_that(test_name_of_symbol(FUNCTION_NAME), is_equal_to_string(TEST_NAME));
}

Ensure(Runner, can_get_context_name_of_name) {
    assert_that(context_name_of("Context:Test"), is_equal_to_string("Context"));
    assert_that(context_name_of("Test"), is_equal_to_string(CGREEN_DEFAULT_SUITE));
}

Ensure(Runner, can_get_test_name_of_name) {
    assert_that(test_name_of("Context:Test"), is_equal_to_string("Test"));
    assert_that(test_name_of("Test"), is_equal_to_string("Test"));
}

Ensure(Runner, can_mangle_default_context_and_test_name_into_function_name) {
    assert_that(mangle_test_name(TEST_NAME), is_equal_to_string(FUNCTION_NAME_WITH_DEFAULT_CONTEXT));
}

Ensure(Runner, can_mangle_explicit_context_and_test_name_into_function_name) {
    assert_that(mangle_test_name(CONTEXT_NAME ":" TEST_NAME), is_equal_to_string(FUNCTION_NAME));
}

Ensure(Runner, can_identify_cgreen_spec) {
    assert_that(is_cgreen_spec("_CgreenSpec__Runner__can_get_test_name_from_function"));
}

Ensure(Runner, can_identify_a_cxx_mangled_cgreen_spec) {
    assert_that(is_cgreen_spec("__ZN6cgreen51CgreenSpec__Runner__can_get_test_name_from_functionE"));
}

Ensure(Runner, can_register_context_and_test_from_a_symbol) {
    TestItem test_items[2] = {{NULL, NULL, NULL}};
    register_test(test_items, 2, FUNCTION_NAME);
    assert_that(test_items[0].context, is_equal_to_string(CONTEXT_NAME));
    assert_that(test_items[0].name, is_equal_to_string(TEST_NAME));
}

Ensure(Runner, can_ensure_test_exists_from_context_and_name) {
    TestItem test_items[5] = {{(char *)"", "Context1", "Test1"},
                              {(char *)"", "Context1", "Test2"},
                              {(char *)"", "Context2", "Test1"},
                              {(char *)"", "Context2", "Test2"},
                              {NULL, NULL, NULL}};
    assert_that(matching_test_exists("Context1:Test1", test_items));
}

Ensure(Runner, can_match_test_name) {
    TestItem test_item = {(char *)"", "Context1", "Test1"};
    assert_that(test_name_matches("Context1:Test1", test_item));
    assert_that(test_name_matches("Context*:Test*", test_item));
}

Ensure(Runner, can_add_test_to_the_suite_for_its_context) {
	ContextSuite *suite_list = NULL;
	CgreenTest *test = (CgreenTest *)&test;
	TestSuite *parent_suite = create_test_suite();

	assert_that(suite_list, is_null);

	add_test_to_context(parent_suite, &suite_list, "TheFirstContext", "TheName", test);
	assert_that(suite_for_context(suite_list, "TheFirstContext")->size, is_equal_to(1));
	assert_that(suite_for_context(suite_list, "TheSecondContext"), is_null);

	add_test_to_context(parent_suite, &suite_list, "TheSecondContext", "TheName", test);
	assert_that(suite_for_context(suite_list, "TheFirstContext")->size, is_equal_to(1));
	assert_that(suite_for_context(suite_list, "TheSecondContext")->size, is_equal_to(1));
}


#ifdef __cplusplus
} // namespace cgreen
#endif

/* vim: set ts=4 sw=4 et cindent: */
/* Local variables: */
/* tab-width: 4     */
/* End:             */
