(require 's)

(defun c++-include-guard-from-classname (classname)
  (concat (s-upcase (s-replace "-" "_" (s-dashed-words classname))) "_H"))

(c++-include-guard-from-classname "GhostAgent")

(define-skeleton c++-header-skel
  "C++ Header Skeleton"
  ""
  '(setq str (skeleton-read "Classname: "))
  '(c++-mode)
  "// -*- C++ -*-\n"
  "#ifndef " (c++-include-guard-from-classname str) "\n"
  "#define " (c++-include-guard-from-classname str) "\n"
  "\n"
  "class " str " {\n"
  _
  "public:\n"
  "  " str "() {\n"
  "  }\n"
  "};\n"
  "\n"
  "#endif//" (c++-include-guard-from-classname str) "\n"
  )
