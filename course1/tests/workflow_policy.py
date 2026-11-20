"""Read-only HOST CI policy, checked before any build."""
from pathlib import Path
import re
text=(Path(__file__).resolve().parents[2]/'.github/workflows/host.yml').read_text()
assert 'permissions:\n  contents: read' in text
assert 'persist-credentials: false' in text
assert 'pull_request_target' not in text and 'secrets.' not in text and 'write' not in text
assert 'ubuntu-24.04' in text and 'macos-15' in text
assert all(re.fullmatch(r'actions/[a-z-]+@[0-9a-f]{40}',x) for x in re.findall(r'uses:\s+(\S+)',text))
print('PASS: read-only pinned-action HOST CI policy.')
