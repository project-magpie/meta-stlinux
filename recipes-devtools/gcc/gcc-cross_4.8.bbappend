FILESEXTRAPATHS := "${THISDIR}/gcc"
PRINC := "${@int(PRINC) + 1}"

SRC_URI += "file://fix_PR58314_unsatisfied_constraints.patch"
