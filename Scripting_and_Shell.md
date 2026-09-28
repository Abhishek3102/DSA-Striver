# Shell / Scripting Languages — Interview Prep Guide

## Why interviewers ask this

They don't expect a 100-line bash script. They test:
1. Are you comfortable on a Linux terminal? (all servers run Linux)
2. Can you debug a running app (logs, processes, ports)?
3. Can you automate small repetitive tasks (usually with Python)?

The winning combo in 2026: **bash basics for survival + Python for real scripting.**

---

## Part 1: Linux/Bash Fundamentals

### 1.1 File system & navigation

```bash
pwd                     # print current directory
ls -la                  # list all files (hidden too) with permissions
cd /var/log             # absolute path
cd ..                   # one level up
cd -                    # go to previous directory (interviewers love this)
tree -L 2               # directory structure, 2 levels deep
```

### 1.2 File operations

```bash
cp file.txt backup/          # copy
mv old.txt new.txt           # rename (move)
rm -rf node_modules          # delete recursively+force (careful!)
mkdir -p src/components      # create nested dirs
touch file.txt               # create empty file
cat file.txt                 # print file
head -n 20 file.txt          # first 20 lines
tail -f app.log              # FOLLOW a log live (you WILL use this daily)
wc -l file.txt               # count lines
find . -name "*.log"         # find files by name
```

### 1.3 File permissions (very common interview question)

```bash
ls -la
# -rw-r--r-- 1 user group 1024 Jan 5 app.py

# Breakdown:  -  rw-  r--  r--
#             |   |    |    +-- others: read only
#             |   |    +------- group: read only
#             |   +------------ owner: read+write
#             +---------------- file type (- file, d directory)

chmod 755 script.sh    # rwxr-xr-x - owner: all, group/others: read+execute
chmod +x script.sh     # make executable
chmod 600 .env         # owner read+write only (protect secrets this way!)
chown user:group file  # change ownership

# Numeric: r=4, w=2, x=1
# 7 = 4+2+1 (rwx), 6 = rw, 5 = r-x, 4 = r
```

**Interview Q: "Difference between 644 and 755?"**
- 644: owner edits, everyone reads (normal files)
- 755: owner executes, others read+execute (scripts, binaries)


### 1.4 Pipes & redirection (the core shell skill)

```bash
# |  pipes output of one command into another
# >  redirects output to a file (overwrites)
# >> appends to a file
# 2> redirects errors
# &> redirects both stdout and stderr

grep "ERROR" app.log > errors.txt      # save all ERROR lines
grep "ERROR" app.log | wc -l           # count errors
cat access.log | grep "404" | head -5  # first 5 404s
ps aux | grep node                     # find node processes
history | tail -20                     # last 20 commands
```

### 1.5 grep / awk / sed (text processing - asked a lot)

```bash
grep -i "error" app.log        # case-insensitive search
grep -c "ERROR" app.log        # COUNT matching lines
grep -rn "TODO" src/           # recursive + show line numbers
grep -v "DEBUG" app.log        # -v = invert (everything EXCEPT debug)
grep -A 3 "Exception" app.log  # show 3 lines After the match
grep -B 3 "Exception" app.log  # 3 lines Before

# awk - column-based extraction
awk '{print $1}' access.log            # first column (IPs)
awk '{s += $1} END {print s}' nums.txt # sum a column

# sed - substitution
sed 's/foo/bar/g' file.txt             # replace all foo with bar (print)
sed -i 's/foo/bar/g' file.txt          # -i = edit file in place
```

**Classic interview task: "Find the 10 most frequent IPs in an access log"**
```bash
awk '{print $1}' access.log | sort | uniq -c | sort -rn | head -10
# print col 1 -> sort (groups duplicates) -> uniq -c counts -> sort -rn numeric reverse -> top 10
```
Explain WHY `sort` is needed before `uniq` (uniq only collapses ADJACENT duplicates).

### 1.6 Processes & system monitoring

```bash
ps aux                  # all running processes
ps aux | grep python    # find python processes
top / htop              # live CPU/memory view
kill -9 12345           # force-kill process with PID 12345
kill -15 12345          # graceful kill (SIGTERM) - default kill
nohup python app.py &   # keep running after logout, in background

df -h                   # disk space
free -h                 # memory usage
du -sh folder/          # size of a folder
uptime                  # how long system is up + load average
```

**Interview Q: "kill -9 vs kill -15?"**
- -15 (SIGTERM): asks the process to shut down cleanly (cleanup handlers run)
- -9 (SIGKILL): kernel kills it immediately, no cleanup
- Always try -15 first.


### 1.7 Environment variables & cron

```bash
export DATABASE_URL="postgres://..."    # set for current session
echo $DATABASE_URL                      # read
printenv | grep DB                      # list all
source .env                             # load variables from a file
which python                            # which python binary is running
```

**cron - scheduled jobs (very common interview topic):**
```bash
crontab -e
# * * * * *  command
# | | | | |
# | | | | +-- day of week (0-7)
# | | | +---- month (1-12)
# | | +------ day of month (1-31)
# | +-------- hour (0-23)
# +---------- minute (0-59)

# Examples:
0 2 * * *     /home/user/backup.sh     # every day at 2 AM
*/15 * * * *  python cleanup.py        # every 15 minutes
0 0 1 * *     /opt/report.sh           # 1st of every month, midnight
```

**Interview Q: "What is shebang?"**
First line of a script: `#!/bin/bash` or `#!/usr/bin/env python3`. Tells the OS which interpreter to use.

### 1.8 A minimal bash script (know how to READ this)

```bash
#!/bin/bash

# variables
NAME="world"
echo "hello $NAME"

# arguments: $1, $2 ...  $# = count,  $@ = all args
echo "first arg: $1"

# if
if [ -f "app.log" ]; then
    echo "log exists"
fi
# -f file exists, -d dir exists, -z string empty, -eq numbers equal

# loop
for f in *.log; do
    echo "found $f"
done

# command result into a variable
COUNT=$(grep -c ERROR app.log)
echo "errors: $COUNT"

# exit codes: 0 = success, non-zero = failure; $? holds last exit code
grep -q "ERROR" app.log && echo "has errors" || echo "clean"
```

**Interview Q: "What does `$?` mean?"**
Exit status of the last command. 0 = success. CI/CD pipelines fail builds based on non-zero exit codes.

### 1.9 Networking / debugging commands

```bash
curl https://api.example.com/users            # HTTP GET
curl -X POST -H "Content-Type: application/json" \
     -d '{"name":"ashish"}' http://localhost:8000/api

---

## Part 2: Python as a Scripting Language (the higher-value skill)

### 2.1 Classic interview tasks

**Parse a log file and count errors by type:**
```python
from collections import Counter

errors = Counter()
with open("app.log") as f:
    for line in f:
        if "ERROR" in line:
            parts = line.split()
            if len(parts) >= 3:
                errors[parts[2]] += 1   # e.g. "2026-01-05 ERROR TimeoutError: ..."

for err, count in errors.most_common(5):
    print(err, count)
```

**Call an API and save the result (they love this one):**
```python
import requests

resp = requests.get("https://jsonplaceholder.typicode.com/users", timeout=10)
resp.raise_for_status()                # throws on 4xx/5xx
users = resp.json()

for u in users[:5]:
    print(u["id"], u["name"], u["email"])

# POST with auth header
r = requests.post(
    "http://localhost:8000/api/items",
    json={"name": "item1"},
    headers={"Authorization": "Bearer <token>"},
    timeout=10,
)
```

**Batch rename files / automation:**
```python
from pathlib import Path

for f in Path("logs").glob("*.txt"):
    new_name = f.name.replace(" ", "_").lower()
    f.rename(f.parent / new_name)
```

**CSV processing (data-role interviewers ask this):**
```python
import csv

with open("users.csv", newline="") as f:
    for row in csv.DictReader(f):
        print(row["name"], row["email"])
```

### 2.2 Scripting-grade Python concepts (know these cold)

```python
# argparse - scripts that take flags
import argparse
p = argparse.ArgumentParser()
p.add_argument("--input", required=True)
p.add_argument("--count", type=int, default=10)
args = p.parse_args()
# run: python script.py --input data.csv --count 5

# json read/write
import json
data = json.load(open("config.json"))           # file -> dict
json.dump(data, open("out.json", "w"), indent=2)
text = json.dumps({"a": 1})                     # dict -> string

# os / sys / pathlib
import os, sys
os.environ.get("API_KEY")        # read env var (never hardcode secrets)
sys.argv                         # raw CLI args
from pathlib import Path
Path("a/b.txt").exists()

# subprocess - run shell commands from Python
import subprocess
result = subprocess.run(["git", "status"], capture_output=True, text=True)
print(result.stdout, result.returncode)

# datetime
from datetime import datetime, timedelta
now = datetime.now()
yesterday = now - timedelta(days=1)
now.strftime("%Y-%m-%d %H:%M:%S")
```

### 2.3 bash vs Python - which to use when?

| Task | Use |
|---|---|
| glue 2-3 shell commands together | bash one-liner |
| anything with loops/conditions over ~20 lines | Python |
| JSON / CSV / API work | Python |
| log parsing | either, Python is cleaner |
| scheduled maintenance (restart, cleanup) | bash + cron |
| anything maintained long-term | Python |

### 2.4 Real answers to common interview questions

**Q: "Find and delete all .tmp files older than 7 days?"**
```bash
find . -name "*.tmp" -mtime +7            # list them FIRST (always check)
find . -name "*.tmp" -mtime +7 -delete    # then delete
```

**Q: "Check disk usage and free memory on a server?"**
```bash
df -h        # disk
free -h      # memory
du -sh /var  # size of one directory
```

**Q: "Your app is down. Walk me through debugging."**
1. `ps aux | grep app` - is the process even running?
2. `tail -100 /var/log/app.log` - what does the log say?
3. `lsof -i :8000` - port conflict?
4. `df -h` / `free -h` - disk full? OOM kill?
5. `systemctl status app` - restart with `systemctl restart app`

This structured answer impresses more than knowing any single command.

### 2.5 Night-before cheat sheet

| Command | Purpose |
|---|---|
| `tail -f log` | live-follow logs |
| `grep -rn "x" .` | search text recursively |
| `ps aux \| grep x` | find process |
| `lsof -i :PORT` | who owns a port |
| `chmod 755 f` | permissions |
| `df -h` / `free -h` | disk / memory |
| `curl -X POST ...` | test APIs |
| `awk '{print $1}'` | extract column |
| `sort \| uniq -c \| sort -rn` | frequency count |
| `find . -name "*.x" -mtime +7` | find old files |

### 2.6 Bottom line for scripting
- Learn the ~20 commands above deeply, not 200 commands shallowly.
- Do NOT over-invest in bash scripting beyond this - Python covers the real work.
- Be ready to narrate the "server is down" debugging story out loud.



