#!/usr/bin/env python3
"""
Main visualization script for Altair datagen analytics.
Reads CSV files from analyze_raw output and generates plots.
"""

import argparse
import os
import sys
from pathlib import Path

import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import numpy as np

# Import individual plot modules
from eval_distribution import plot_eval_histogram, format_eval_bucket_label
from material_distribution import plot_material_stats
from position_stats import plot_position_stats


def load_summary(analytics_dir: Path) -> dict:
    """Load summary.csv into a dictionary."""
    summary_path = analytics_dir / "summary.csv"
    if not summary_path.exists():
        return {}

    df = pd.read_csv(summary_path)
    return dict(zip(df['metric'], df['value']))


def create_overview_figure(analytics_dir: Path, output_dir: Path):
    """Create a multi-panel overview figure."""
    fig = plt.figure(figsize=(16, 12))
    gs = gridspec.GridSpec(3, 3, figure=fig, hspace=0.3, wspace=0.3)

    summary = load_summary(analytics_dir)

    # Title with summary stats
    title = f"Altair Datagen Analytics\n"
    title += f"Total: {int(float(summary.get('total_records', 0))):,} records"
    title += f" | Unique: ~{int(float(summary.get('estimated_unique', 0))):,}"
    title += f" | Dup ratio: {float(summary.get('duplicate_ratio', 0))*100:.1f}%"
    fig.suptitle(title, fontsize=14, fontweight='bold')

    # WDL pie chart
    ax1 = fig.add_subplot(gs[0, 0])
    wdl_path = analytics_dir / "wdl_distribution.csv"
    if wdl_path.exists():
        wdl = pd.read_csv(wdl_path)
        colors = ['#2ecc71', '#95a5a6', '#e74c3c']  # green, gray, red
        ax1.pie(wdl['count'], labels=['Win', 'Draw', 'Loss'],
                autopct='%1.1f%%', colors=colors, startangle=90)
        ax1.set_title('WDL Distribution')

    # Side to move bar chart
    ax2 = fig.add_subplot(gs[0, 1])
    stm_path = analytics_dir / "side_to_move.csv"
    if stm_path.exists():
        stm = pd.read_csv(stm_path)
        colors = ['#ffffff', '#333333']
        bars = ax2.bar(stm['side'], stm['count'], color=colors, edgecolor='black')
        ax2.set_title('Side to Move')
        ax2.set_ylabel('Count')
        for bar, pct in zip(bars, stm['percentage']):
            ax2.text(bar.get_x() + bar.get_width()/2, bar.get_height(),
                    f'{pct:.1f}%', ha='center', va='bottom')

    # Eval histogram
    ax3 = fig.add_subplot(gs[0, 2])
    eval_path = analytics_dir / "eval_histogram.csv"
    if eval_path.exists():
        eval_df = pd.read_csv(eval_path)
        labels = [
            format_eval_bucket_label(int(r['bucket_min']), int(r['bucket_max']))
            for _, r in eval_df.iterrows()
        ]
        ax3.bar(range(len(eval_df)), eval_df['count'], color='steelblue')
        tick_step = max(1, len(eval_df) // 6)
        tick_positions = list(range(0, len(eval_df), tick_step))
        if tick_positions[-1] != len(eval_df) - 1:
            tick_positions.append(len(eval_df) - 1)
        ax3.set_xticks(tick_positions)
        ax3.set_xticklabels([labels[i] for i in tick_positions], rotation=45, ha='right')
        ax3.set_title('Eval Distribution')
        ax3.set_ylabel('Count')
        ax3.set_xlabel('Centipawns')

    # Castling rights distribution
    ax4 = fig.add_subplot(gs[1, 0])
    castle_path = analytics_dir / "castling_rights.csv"
    if castle_path.exists():
        castle = pd.read_csv(castle_path)
        # Show top 8 castling combinations
        top_castle = castle.nlargest(8, 'count')
        ax4.barh(top_castle['castling_rights'], top_castle['count'], color='coral')
        ax4.set_title('Castling Rights (Top 8)')
        ax4.set_xlabel('Count')

    # King position heatmaps
    ax5 = fig.add_subplot(gs[1, 1])
    ax6 = fig.add_subplot(gs[1, 2])
    king_path = analytics_dir / "king_positions.csv"
    if king_path.exists():
        kings = pd.read_csv(king_path)

        # Reshape to 8x8 boards
        wk_board = np.zeros((8, 8))
        bk_board = np.zeros((8, 8))
        for _, row in kings.iterrows():
            f, r = int(row['file']), int(row['rank'])
            wk_board[r, f] = row['white_king_count']
            bk_board[r, f] = row['black_king_count']

        # Plot heatmaps (flip so rank 1 is at bottom)
        im1 = ax5.imshow(wk_board[::-1], cmap='Oranges', aspect='equal')
        ax5.set_title('White King Positions')
        ax5.set_xticks(range(8))
        ax5.set_xticklabels(['a','b','c','d','e','f','g','h'])
        ax5.set_yticks(range(8))
        ax5.set_yticklabels(['8','7','6','5','4','3','2','1'])
        plt.colorbar(im1, ax=ax5, shrink=0.6)

        im2 = ax6.imshow(bk_board[::-1], cmap='Blues', aspect='equal')
        ax6.set_title('Black King Positions')
        ax6.set_xticks(range(8))
        ax6.set_xticklabels(['a','b','c','d','e','f','g','h'])
        ax6.set_yticks(range(8))
        ax6.set_yticklabels(['8','7','6','5','4','3','2','1'])
        plt.colorbar(im2, ax=ax6, shrink=0.6)

    # Material distribution (simplified)
    ax7 = fig.add_subplot(gs[2, :])
    piece_path = analytics_dir / "piece_counts.csv"
    if piece_path.exists():
        pieces = pd.read_csv(piece_path)
        # Show average piece counts
        piece_names = pieces['piece_type'].tolist()

        # Calculate weighted average for each piece
        avg_counts = []
        for _, row in pieces.iterrows():
            total = sum(row[f'count_{i}'] * i for i in range(11))
            total_positions = sum(row[f'count_{i}'] for i in range(11))
            avg = total / total_positions if total_positions > 0 else 0
            avg_counts.append(avg)

        colors = ['#f39c12'] * 5 + ['#2c3e50'] * 5  # Orange for white, dark for black
        ax7.bar(piece_names, avg_counts, color=colors)
        ax7.set_title('Average Piece Counts')
        ax7.set_ylabel('Average Count')
        ax7.axhline(y=0, color='black', linewidth=0.5)
        plt.xticks(rotation=45)

    plt.tight_layout(rect=[0, 0, 1, 0.95])

    output_path = output_dir / "overview.png"
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    print(f"Saved: {output_path}")
    plt.close()


def main():
    parser = argparse.ArgumentParser(
        description='Visualize Altair datagen analytics from CSV files'
    )
    parser.add_argument('analytics_dir', type=Path,
                        help='Directory containing analytics CSV files')
    parser.add_argument('-o', '--output', type=Path, default=Path('plots'),
                        help='Output directory for plots (default: plots)')
    parser.add_argument('--dpi', type=int, default=150,
                        help='DPI for output images (default: 150)')

    args = parser.parse_args()

    if not args.analytics_dir.exists():
        print(f"Error: Analytics directory not found: {args.analytics_dir}")
        sys.exit(1)

    args.output.mkdir(parents=True, exist_ok=True)

    print(f"Reading analytics from: {args.analytics_dir}")
    print(f"Writing plots to: {args.output}")

    # Create overview figure
    create_overview_figure(args.analytics_dir, args.output)

    # Create individual plots
    plot_eval_histogram(args.analytics_dir, args.output)
    plot_material_stats(args.analytics_dir, args.output)
    plot_position_stats(args.analytics_dir, args.output)

    print("\nDone!")


if __name__ == "__main__":
    main()
