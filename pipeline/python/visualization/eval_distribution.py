#!/usr/bin/env python3
"""Evaluation distribution plots."""

from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def format_eval_bucket_label(bucket_min: int, bucket_max: int) -> str:
    """Format a readable eval bucket label."""
    if bucket_min <= -100000:
        return f"< {bucket_max}"
    if bucket_max >= 100000:
        return f">= {bucket_min}"
    return f"[{bucket_min}, {bucket_max})"


def plot_eval_histogram(analytics_dir: Path, output_dir: Path):
    """Create detailed eval distribution plot."""
    eval_path = analytics_dir / "eval_histogram.csv"
    if not eval_path.exists():
        print("Warning: eval_histogram.csv not found")
        return

    df = pd.read_csv(eval_path)

    fig, axes = plt.subplots(1, 2, figsize=(14, 5))

    # Full histogram
    ax1 = axes[0]
    labels = [format_eval_bucket_label(int(r['bucket_min']), int(r['bucket_max'])) for _, r in df.iterrows()]
    x = range(len(df))
    bars = ax1.bar(x, df['count'], color='steelblue', edgecolor='navy', alpha=0.8)

    ax1.set_xticks(list(x))
    ax1.set_xticklabels(labels, rotation=45, ha='right', fontsize=8)
    ax1.set_title('Evaluation Distribution (All Buckets)', fontweight='bold')
    ax1.set_ylabel('Count')
    ax1.set_xlabel('Centipawn Range')

    # Add percentage labels on top of bars
    total = df['count'].sum()
    for bar, count in zip(bars, df['count']):
        if count > 0:
            pct = 100 * count / total
            if pct > 1:  # Only show if > 1%
                ax1.text(bar.get_x() + bar.get_width()/2, bar.get_height(),
                        f'{pct:.1f}%', ha='center', va='bottom', fontsize=7)

    # Log scale version
    ax2 = axes[1]
    ax2.bar(x, df['count'], color='coral', edgecolor='darkred', alpha=0.8)
    ax2.set_yscale('log')
    ax2.set_xticks(list(x))
    ax2.set_xticklabels(labels, rotation=45, ha='right', fontsize=8)
    ax2.set_title('Evaluation Distribution (Log Scale)', fontweight='bold')
    ax2.set_ylabel('Count (log)')
    ax2.set_xlabel('Centipawn Range')

    plt.tight_layout()
    output_path = output_dir / "eval_distribution.png"
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    print(f"Saved: {output_path}")
    plt.close()


def plot_eval_cumulative(analytics_dir: Path, output_dir: Path):
    """Create cumulative distribution plot."""
    eval_path = analytics_dir / "eval_histogram.csv"
    if not eval_path.exists():
        return

    df = pd.read_csv(eval_path)

    fig, ax = plt.subplots(figsize=(10, 5))

    # Cumulative from negative to positive
    cumsum = df['count'].cumsum()
    total = df['count'].sum()
    cumulative_pct = 100 * cumsum / total

    # Use bucket midpoints for x-axis
    midpoints = [(r['bucket_min'] + r['bucket_max']) / 2 for _, r in df.iterrows()]

    ax.plot(midpoints, cumulative_pct, 'b-', linewidth=2, marker='o', markersize=4)
    ax.axhline(50, color='gray', linestyle='--', alpha=0.5, label='50%')
    ax.axhline(95, color='gray', linestyle=':', alpha=0.5, label='95%')
    ax.axvline(0, color='red', linestyle='-', alpha=0.3, label='Equal eval')

    ax.set_xlabel('Centipawns')
    ax.set_ylabel('Cumulative %')
    ax.set_title('Cumulative Evaluation Distribution', fontweight='bold')
    ax.legend()
    ax.grid(True, alpha=0.3)
    ax.set_xlim(-5500, 5500)
    ax.set_ylim(0, 100)

    plt.tight_layout()
    output_path = output_dir / "eval_cumulative.png"
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    print(f"Saved: {output_path}")
    plt.close()


if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python eval_distribution.py <analytics_dir> [output_dir]")
        sys.exit(1)

    analytics_dir = Path(sys.argv[1])
    output_dir = Path(sys.argv[2]) if len(sys.argv) > 2 else Path("plots")
    output_dir.mkdir(exist_ok=True)

    plot_eval_histogram(analytics_dir, output_dir)
    plot_eval_cumulative(analytics_dir, output_dir)
