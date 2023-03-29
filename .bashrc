# PS1 configuration
export HOME=${PWD};
export PS1='\[[1m\]\[[34m\]$PWD\[[32m\] \$\[(B[m\] ';

# command runtime function
function timer_start {
  timer=${timer:-$SECONDS}
}

function timer_stop {
  timer_show=$(($SECONDS - $timer))
  unset timer
}

trap 'timer_start' DEBUG
PROMPT_COMMAND=timer_stop

# new PS1 with command runtime
PS1='\[[0;1;93m\][\[[0;1;93m\]last: ${timer_show}s\[[0;1;93m\]] \[[0;1;94m\]$PWD \[[0;1;92m\]$ \[[0m\]'

## Aliases
alias ls='ls --color=auto';
alias ll='ls -lh';
alias ag='ag --color';
alias less='less -R';
#add esb tools bash aliases
source /app/shell_tools/bash_aliases
