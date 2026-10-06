#!/usr/bin/env bash
# =========================================================
# Cross-compile LMS_GUI.exe for 64-bit Windows from Linux.
#
# Needs (paths can be overridden with environment variables):
#   QT_WIN   Qt for Windows, llvm-mingw build  (e.g. .../6.10.2/llvm-mingw_64)
#   QT_HOST  Qt for Linux, same version        (for moc and rcc)
#   LLVM_MINGW  llvm-mingw toolchain for Linux (17.0.6, ucrt)
#
# Output: dist/LMS_GUI/  (exe + Qt DLLs)  and  dist/LMS_GUI-windows-x64.zip
#
# On Windows itself you do not need this: just open LMS_GUI.pro
# in Qt Creator and press Run.
# =========================================================
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
: "${QT_WIN:?set QT_WIN to the Windows llvm-mingw Qt folder}"
: "${QT_HOST:?set QT_HOST to the Linux Qt folder of the same version}"
: "${LLVM_MINGW:?set LLVM_MINGW to the llvm-mingw toolchain folder}"

CXX="$LLVM_MINGW/bin/x86_64-w64-mingw32-clang++"
MOC="$QT_HOST/libexec/moc"
RCC="$QT_HOST/libexec/rcc"
OBJ="$ROOT/dist/obj"
OUT="$ROOT/dist/LMS_GUI"

rm -rf "$ROOT/dist"
mkdir -p "$OBJ" "$OUT/platforms" "$OUT/styles"

DEFINES=(-DUNICODE -D_UNICODE -DWIN32 -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB)
INCLUDES=(-I"$ROOT/src" -I"$ROOT" -I"$QT_WIN/include" -I"$QT_WIN/include/QtCore"
          -I"$QT_WIN/include/QtGui" -I"$QT_WIN/include/QtWidgets" -I"$QT_WIN/mkspecs/win32-clang-g++")
CXXFLAGS=(-std=c++17 -O2 -Wall -Wextra -Wno-ignored-attributes "${DEFINES[@]}" "${INCLUDES[@]}")

# ---- 1. moc: every header with Q_OBJECT ----
SOURCES=("$ROOT/main.cpp")
while IFS= read -r file; do SOURCES+=("$file"); done < <(find "$ROOT/src" -name '*.cpp' | sort)

for header in $(grep -rl Q_OBJECT "$ROOT/src" --include='*.h' | sort); do
    name="$(basename "$header" .h)"
    "$MOC" "${DEFINES[@]}" "${INCLUDES[@]}" "$header" -o "$OBJ/moc_$name.cpp"
    SOURCES+=("$OBJ/moc_$name.cpp")
done

# ---- 2. rcc: stylesheet + sample CSV files ----
"$RCC" --no-zstd -name resources "$ROOT/resources/resources.qrc" -o "$OBJ/qrc_resources.cpp"
SOURCES+=("$OBJ/qrc_resources.cpp")

# ---- 3. compile (in parallel) ----
pids=()
index=0
for source in "${SOURCES[@]}"; do
    object="$OBJ/$(printf '%03d' "$index")_$(basename "${source%.cpp}").o"
    "$CXX" "${CXXFLAGS[@]}" -c "$source" -o "$object" &
    pids+=($!)
    index=$((index + 1))
done
for pid in "${pids[@]}"; do
    wait "$pid"     # set -e stops the script if any file failed
done

# ---- 4. link (-mwindows = no console window; EntryPoint provides WinMain) ----
"$CXX" -mwindows -o "$OUT/LMS_GUI.exe" "$OBJ"/*.o \
    -L"$QT_WIN/lib" -lQt6EntryPoint -lQt6Widgets -lQt6Gui -lQt6Core -lshell32

# ---- 5. copy the DLLs the exe needs ----
for dll in Qt6Core Qt6Gui Qt6Widgets; do
    cp "$QT_WIN/bin/$dll.dll" "$OUT/"
done
cp "$QT_WIN/plugins/platforms/qwindows.dll" "$OUT/platforms/"
cp "$QT_WIN"/plugins/styles/*.dll "$OUT/styles/" 2>/dev/null || true
for dll in libc++.dll libunwind.dll; do
    cp "$LLVM_MINGW/x86_64-w64-mingw32/bin/$dll" "$OUT/"
done

# ---- 6. zip ----
(cd "$ROOT/dist" && rm -f LMS_GUI-windows-x64.zip && zip -qr LMS_GUI-windows-x64.zip LMS_GUI)
echo "Built $OUT/LMS_GUI.exe"
echo "Zip:  $ROOT/dist/LMS_GUI-windows-x64.zip"
