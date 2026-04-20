#!/usr/bin/env python3
"""Position statistics plots (king positions, castling, side to move)."""

from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def plot_position_stats(analytics_dir: Path, output_dir: Path):
    """Create all position-related plots."""
    plot_king_heatmaps(analytics_dir, output_dir)
    plot_castling_distribution(analytics_dir, output_dir)
    plot_side_to_move(analytics_dir, output_dir)


def plot_king_heatmaps(analytics_dir: Path, output_dir: Path):
    """Create king position heatmaps."""
    king_path = analytics_dir / "king_positions.csv"
    if not king_path.exists():
        print("Warning: king_positions.csv not found")
        return

    df = pd.read_csv(king_path)

    fig, axes = plt.subplots(1, 2, figsize=(12, 5))

    # Reshape to 8x8 boards
    wk_board = np.zeros((8, 8))
    bk_board = np.zeros((8, 8))
    for _, row in df.iterrows():
        f, r = int(row['file']), int(row['rank'])
        wk_board[r, f] = row['white_king_count']
        bk_board[r, f] = row['black_king_count']

    # Normalize for better visualization
    wk_norm = wk_board / wk_board.max() if wk_board.max() > 0 else wk_board
    bk_norm = bk_board / bk_board.max() if bk_board.max() > 0 else bk_board

    # Plot White king heatmap
    ax1 = axes[0]
    im1 = ax1.imshow(wk_norm[::-1], cmap='YlOrRd', aspect='equal', vmin=0, vmax=1)
    ax1.set_title('White King Positions', fontsize=12, fontweight='bold')
    ax1.set_xticks(range(8))
    ax1.set_xticklabels(['a','b','c','d','e','f','g','h'])
    ax1.set_yticks(range(8))
    ax1.set_yticklabels(['8','7','6','5','4','3','2','1'])

    # Add count annotations
    for r in range(8):
        for f in range(8):
            count = int(wk_board[7-r, f])
            if count > 0:
                color = 'white' if wk_norm[7-r, f] > 0.5 else 'black'
                ax1.text(f, r, f'{count}', ha='center', va='center',
                        fontsize=7, color=color)

    plt.colorbar(im1, ax=ax1, shrink=0.8, label='Relative frequency')

    # Plot Black king heatmap
    ax2 = axes[1]
    im2 = ax2.imshow(bk_norm[::-1], cmap='YlGnBu', aspect='equal', vmin=0, vmax=1)
    ax2.set_title('Black King Positions', fontsize=12, fontweight='bold')
    ax2.set_xticks(range(8))
    ax2.set_xticklabels(['a','b','c','d','e','f','g','h'])
    ax2.set_yticks(range(8))
    ax2.set_yticklabels(['8','7','6','5','4','3','2','1'])

    # Add count annotations
    for r in range(8):
        for f in range(8):
            count = int(bk_board[7-r, f])
            if count > 0:
                color = 'white' if bk_norm[7-r, f] > 0.5 else 'black'
                ax2.text(f, r, f'{count}', ha='center', va='center',
                        fontsize=7, color=color)

    plt.colorbar(im2, ax=ax2, shrink=0.8, label='Relative frequency')

    plt.suptitle('King Position Distributions', fontsize=14, fontweight='bold')
    plt.tight_layout(rect=[0, 0, 1, 0.95])

    output_path = output_dir / "king_positions.png"
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    print(f"Saved: {output_path}")
    plt.close()


def plot_castling_distribution(analytics_dir: Path, output_dir: Path):
    """Plot castling rights distribution."""
    castle_path = analytics_dir / "castling_rights.csv"
    if not castle_path.exists():
        print("Warning: castling_rights.csv not found")
        return

    df = pd.read_csv(castle_path)

    fig, axes = plt.subplots(1, 2, figsize=(14, 5))

    # Bar chart of all castling combinations
    ax1 = axes[0]
    x = range(len(df))
    bars = ax1.bar(x, df['count'], color='mediumpurple', edgecolor='purple', alpha=0.8)
    ax1.set_xticks(x)
    ax1.set_xticklabels(df['castling_rights'], rotation=45, ha='right')
    ax1.set_ylabel('Count')
    ax1.set_title('Castling Rights Distribution', fontsize=12, fontweight='bold')

    # Pie chart of grouped categories
    ax2 = axes[1]

    # Group into categories
    categories = {
        'All (KQkq)': df[df['castling_rights'] == 'KQkq']['count'].sum(),
        'White only': df[(df['K'] == 1) | (df['Q'] == 1)]['count'].sum() -
                     df[(df['k'] == 1) | (df['q'] == 1)]['count'].sum(),
        'Black only': df[(df['k'] == 1) | (df['q'] == 1)]['count'].sum() -
                     df[(df['K'] == 1) | (df['Q'] == 1)]['count'].sum(),
        'None (-)': df[df['castling_rights'] == '-']['count'].sum(),
    }

    # Recalculate properly
    all_rights = df[df['castling_rights'] == 'KQkq']['count'].sum()
    no_rights = df[df['castling_rights'] == '-']['count'].sum()
    white_any = df[(df['K'] == 1) | (df['Q'] == 1)]['count'].sum()
    black_any = df[(df['k'] == 1) | (df['q'] == 1)]['count'].sum()
    both = df[((df['K'] == 1) | (df['Q'] == 1)) & ((df['k'] == 1) | (df['q'] == 1))]['count'].sum()

    categories = {
        'Both sides': both,
        'White only': white_any - both,
        'Black only': black_any - both,
        'None': no_rights,
    }

    colors = ['#3498db', '#f39c12', '#2c3e50', '#95a5a6']
    values = [v for v in categories.values() if v > 0]
    labels = [k for k, v in categories.items() if v > 0]

    if values:
        ax2.pie(values, labels=labels, autopct='%1.1f%%', colors=colors[:len(values)],
               startangle=90)
        ax2.set_title('Castling Rights Summary', fontsize=12, fontweight='bold')

    plt.tight_layout()

    output_path = output_dir / "castling_rights.png"
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    print(f"Saved: {output_path}")
    plt.close()


def plot_side_to_move(analytics_dir: Path, output_dir: Path):
    """Plot side to move distribution."""
    stm_path = analytics_dir / "side_to_move.csv"
    if not stm_path.exists():
        print("Warning: side_to_move.csv not found")
        return

    df = pd.read_csv(stm_path)

    fig, ax = plt.subplots(figsize=(6, 4))

    colors = ['#ecf0f1', '#2c3e50']  # Light for white, dark for black
    bars = ax.bar(df['side'], df['count'], color=colors, edgecolor='black', linewidth=2)

    # Add count labels
    for bar, count, pct in zip(bars, df['count'], df['percentage']):
        ax.text(bar.get_x() + bar.get_width()/2, bar.get_height()/2,
               f'{count:,}\n({pct:.1f}%)', ha='center', va='center',
               fontsize=12, fontweight='bold')

    ax.set_ylabel('Count')
    ax.set_title('Side to Move', fontsize=14, fontweight='bold')
    ax.set_ylim(0, max(df['count']) * 1.1)

    plt.tight_layout()

    output_path = output_dir / "side_to_move.png"
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    print(f"Saved: {output_path}")
    plt.close()


if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python position_stats.py <analytics_dir> [output_dir]")
        sys.exit(1)

    analytics_dir = Path(sys.argv[1])
    output_dir = Path(sys.argv[2]) if len(sys.argv) > 2 else Path("plots")
    output_dir.mkdir(exist_ok=True)

    plot_position_stats(analytics_dir, output_dir)
