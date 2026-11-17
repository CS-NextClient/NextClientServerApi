import argparse
from pathlib import Path
import struct
import subprocess
import zlib


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--compiler', required=True)
    parser.add_argument('--include-dir', required=True)
    parser.add_argument('--api-include', required=True)
    parser.add_argument('--source', required=True)
    parser.add_argument('--output', required=True)
    parser.add_argument('--runner', required=True)
    args = parser.parse_args()
    output = Path(args.output).resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    compile_result = subprocess.run([args.compiler, args.source, '-i' + args.api_include,
                                    '-i' + args.include_dir, '-o' + str(output)],
                                   capture_output=True, text=True)
    diagnostics = compile_result.stdout + compile_result.stderr
    print(diagnostics, end='')
    if compile_result.returncode or 'warning ' in diagnostics:
        return 1
    packed = output.read_bytes()
    magic, version, entries = struct.unpack_from('<IHB', packed)
    if magic != 0x414D5858 or entries != 1:
        raise ValueError('unsupported AMXX container')
    cells, disk_size, image_size, memory_size, offset = struct.unpack_from('<BIIII', packed, 7)
    if cells != 4:
        raise ValueError('test runner requires 32-bit cells')
    image = zlib.decompress(packed[offset:offset + disk_size])
    if len(image) != image_size:
        raise ValueError('unexpected AMX image size')
    raw = output.with_suffix('.amx')
    raw.write_bytes(image)
    return subprocess.run([args.runner, str(raw)]).returncode


if __name__ == '__main__':
    raise SystemExit(main())
