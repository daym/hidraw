#include <Python.h>
#include <sys/ioctl.h>
#include <linux/hidraw.h>

struct module_state {
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#error no
static struct module_state _state;
#endif

static PyObject* get_info(PyObject *self, PyObject *args)
{
	struct hidraw_devinfo info;
	unsigned FD;

	if(!PyArg_ParseTuple(args, "I", &FD))
		return NULL;
	if(ioctl(FD, HIDIOCGRAWINFO, &info) == -1) {
		PyErr_SetFromErrno(PyExc_OSError);
		return NULL;
	}
	return Py_BuildValue("IHH", (unsigned) info.bustype, (unsigned short) info.vendor, (unsigned short) info.product);
}
/* TODO:
#define HIDIOCGRDESCSIZE        _IOR('H', 0x01, int)
#define HIDIOCGRDESC            _IOR('H', 0x02, struct hidraw_report_descriptor
*/

static PyMethodDef hidraw_methods[] = {
	{"get_info",  get_info, METH_VARARGS, "Get HIDRAW device info."},
	{NULL, NULL, 0, NULL}        /* Sentinel */
};

#if PY_MAJOR_VERSION >= 3

static int hidraw_traverse(PyObject *m, visitproc visit, void *arg) {
	//Py_VISIT(GETSTATE(m)->error);
	return 0;
}

static int hidraw_clear(PyObject *m) {
	//Py_CLEAR(GETSTATE(m)->error);
	return 0;
}

static struct PyModuleDef moduledef = {
	PyModuleDef_HEAD_INIT,
	"_hidraw",
	NULL,
	sizeof(struct module_state),
	hidraw_methods,
	NULL,
	hidraw_traverse,
	hidraw_clear,
	NULL
};

PyMODINIT_FUNC
PyInit__hidraw(void)
{
	PyObject *m;

	m = PyModule_Create(&moduledef);
	if (m == NULL) {
		return NULL;
	}
	return m;
}

#else

PyMODINIT_FUNC
init_hidraw(void)
{
	PyObject *m;

	m = Py_InitModule("_hidraw", hidraw_methods);
	if (m == NULL) {
		return;
	}
}

#endif
