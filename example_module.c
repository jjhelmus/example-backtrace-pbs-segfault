#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <execinfo.h>

int boom() {
    int nptrs;
    void *buffer[50];
    printf("In boom\n");
    nptrs = backtrace(buffer, 50);
    printf("nptrs is %i\n", nptrs);
    return 1;
}

// https://docs.python.org/3/extending/newtypes_tutorial.html

// Thing object

typedef struct {
    PyObject_HEAD
    double x;
} ThingObject;

static int
Thing_init(ThingObject *self, PyObject *args, PyObject *kwds)
{
    self->x = 0.0;
    return 0;
}

static PyObject *
Thing_inplace_or(ThingObject *self, PyObject *other)
{
    boom();  // trigger possible segfault
    self->x += 1;
    Py_INCREF(self);
    return (PyObject *)self;
}

static PyNumberMethods Thing_as_number = {
    .nb_inplace_or = (binaryfunc)Thing_inplace_or,
};

static PyMethodDef Thing_methods[] = {
    {NULL}
};

static PyTypeObject ThingType = {
    .ob_base      = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name      = "example.Thing",
    .tp_basicsize = sizeof(ThingObject),
    .tp_flags     = Py_TPFLAGS_DEFAULT,
    .tp_new       = PyType_GenericNew,
    .tp_init      = (initproc)Thing_init,
    .tp_methods   = Thing_methods,
    .tp_as_number = &Thing_as_number,
};

// example module

static int
example_module_exec(PyObject *m)
{
    if (PyType_Ready(&ThingType) < 0) {
        return -1;
    }

    if (PyModule_AddObject(m, "Thing", (PyObject *) &ThingType) < 0) {
        return -1;
    }

    return 0;
}

static PyModuleDef_Slot example_module_slots[] = {
    {Py_mod_exec, example_module_exec},
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
    {0, NULL}
};

static PyModuleDef example_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "example",
    .m_doc = "Example module with an object that can segfault pbs.",
    .m_size = 0,
    .m_slots = example_module_slots,
};

PyMODINIT_FUNC
PyInit_example(void)
{
    return PyModuleDef_Init(&example_module);
}
