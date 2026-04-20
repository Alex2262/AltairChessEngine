#!/usr/bin/env python3
"""Material distribution plots."""

from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


def plot_material_stats(analytics_dir: Path, output_dir: Path):
    """Create material distribution plots."""
    # Piece counts distribution
    piece_path = analytics_dir / "piece_counts.csv"
    if piece_path.exists():
        plot_piece_counts(piece_path, output_dir)

    # Material configurations
    material_path = analytics_dir / "material_distribution.csv"
    if material_path.exists():
        plot_material_configs(material_path, output_dir)

    total_material_path = analytics_dir / "total_material.csv"
    non_pawn_material_path = analytics_dir / "non_pawn_material.csv"
    imbalance_path = analytics_dir / "material_imbalance.csv"
    halfmove_path = analytics_dir / "halfmove_clock.csv"
    if any(path.exists() for path in [total_material_path, non_pawn_material_path, imbalance_path, halfmove_path]):
        plot_material_phase(total_material_path, non_pawn_material_path, imbalance_path, halfmove_path, output_dir)


def plot_piece_counts(piece_path: Path, output_dir: Path):
    """Plot per-piece count distributions."""
    df = pd.read_csv(piece_path)

    fig, axes = plt.subplots(2, 5, figsize=(16, 8))
    axes = axes.flatten()

    piece_names = df['piece_type'].tolist()
    colors = {
        'white': '#f39c12',  # Orange
        'black': '#2c3e50',  # Dark
    }

    for idx, (_, row) in enumerate(df.iterrows()):
        ax = axes[idx]
        piece = row['piece_type']
        counts = [row[f'count_{i}'] for i in range(11)]

        color = colors['white'] if 'white' in piece else colors['black']
        ax.bar(range(11), counts, color=color, edgecolor='black', alpha=0.8)

        ax.set_title(piece.replace('_', ' ').title(), fontsize=10)
        ax.set_xlabel('Count')
        ax.set_ylabel('Positions')
        ax.set_xticks(range(11))

        # Calculate and show average
        total_pos = sum(counts)
        if total_pos > 0:
            avg = sum(i * c for i, c in enumerate(counts)) / total_pos
            ax.axvline(avg, color='red', linestyle='--', alpha=0.7)
            ax.text(0.95, 0.95, f'μ={avg:.2f}', transform=ax.transAxes,
                   ha='right', va='top', fontsize=8, color='red')

    plt.suptitle('Piece Count Distributions', fontsize=14, fontweight='bold')
    plt.tight_layout(rect=[0, 0, 1, 0.96])

    output_path = output_dir / "piece_counts.png"
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    print(f"Saved: {output_path}")
    plt.close()


def plot_material_configs(material_path: Path, output_dir: Path):
    """Plot most common material configurations."""
    df = pd.read_csv(material_path)

    # Take top 20 configurations
    df_top = df.head(20).copy()

    # Create configuration labels
    def make_label(row):
        parts = []
        for color, prefix in [('white', 'W'), ('black', 'B')]:
            pieces = []
            for piece, char in [('pawns', 'P'), ('knights', 'N'), ('bishops', 'B'),
                               ('rooks', 'R'), ('queens', 'Q')]:
                count = int(row[f'{color}_{piece}'])
                if count > 0:
                    pieces.append(f"{count}{char}")
            if pieces:
                parts.append(prefix + ":" + "".join(pieces))
        return " ".join(parts) if parts else "Kings only"

    df_top['label'] = df_top.apply(make_label, axis=1)

    fig, ax = plt.subplots(figsize=(12, 8))

    y_pos = range(len(df_top))
    bars = ax.barh(y_pos, df_top['count'], color='teal', alpha=0.8)

    ax.set_yticks(y_pos)
    ax.set_yticklabels(df_top['label'], fontsize=9)
    ax.invert_yaxis()
    ax.set_xlabel('Count')
    ax.set_title('Top 20 Material Configurations', fontsize=14, fontweight='bold')

    # Add percentage labels
    total = df['count'].sum()
    for bar, count in zip(bars, df_top['count']):
        pct = 100 * count / total
        ax.text(bar.get_width(), bar.get_y() + bar.get_height()/2,
               f' {pct:.1f}%', va='center', fontsize=8)

    plt.tight_layout()

    output_path = output_dir / "material_configs.png"
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    print(f"Saved: {output_path}")
    plt.close()


def plot_material_phase(total_material_path: Path, non_pawn_material_path: Path,
                        imbalance_path: Path, halfmove_path: Path, output_dir: Path):
    """Plot rough phase/material-weight histograms."""
    fig, axes = plt.subplots(2, 2, figsize=(14, 10))
    axes = axes.flatten()

    if total_material_path.exists():
        df = pd.read_csv(total_material_path)
        axes[0].bar(df['total_material'], df['count'], color='slateblue', alpha=0.85)
        axes[0].set_title('Total Material Weight')
        axes[0].set_xlabel('Material')
        axes[0].set_ylabel('Positions')

    if non_pawn_material_path.exists():
        df = pd.read_csv(non_pawn_material_path)
        axes[1].bar(df['non_pawn_material'], df['count'], color='seagreen', alpha=0.85)
        axes[1].set_title('Non-Pawn Material Weight')
        axes[1].set_xlabel('Non-pawn Material')
        axes[1].set_ylabel('Positions')

    if imbalance_path.exists():
        df = pd.read_csv(imbalance_path)
        axes[2].bar(df['material_imbalance'], df['count'], color='indianred', alpha=0.85)
        axes[2].set_title('Material Imbalance (White - Black)')
        axes[2].set_xlabel('Imbalance')
        axes[2].set_ylabel('Positions')

    if halfmove_path.exists():
        df = pd.read_csv(halfmove_path)
        axes[3].bar(df['halfmove_clock'], df['count'], color='darkgoldenrod', alpha=0.85)
        axes[3].set_title('Halfmove Clock Distribution')
        axes[3].set_xlabel('Halfmove Clock')
        axes[3].set_ylabel('Positions')

    plt.suptitle('Material Phase Statistics', fontsize=14, fontweight='bold')
    plt.tight_layout(rect=[0, 0, 1, 0.96])

    output_path = output_dir / "material_phase.png"
    plt.savefig(output_path, dpi=150, bbox_inches='tight')
    print(f"Saved: {output_path}")
    plt.close()


if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python material_distribution.py <analytics_dir> [output_dir]")
        sys.exit(1)

    analytics_dir = Path(sys.argv[1])
    output_dir = Path(sys.argv[2]) if len(sys.argv) > 2 else Path("plots")
    output_dir.mkdir(exist_ok=True)

    plot_material_stats(analytics_dir, output_dir)
