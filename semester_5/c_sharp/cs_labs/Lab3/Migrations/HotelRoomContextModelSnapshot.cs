﻿// <auto-generated />
using System;
using Lab3.Data.Context;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Storage.ValueConversion;
using Npgsql.EntityFrameworkCore.PostgreSQL.Metadata;

#nullable disable

namespace Lab3.Migrations
{
    [DbContext(typeof(HotelRoomContext))]
    partial class HotelRoomContextModelSnapshot : ModelSnapshot
    {
        protected override void BuildModel(ModelBuilder modelBuilder)
        {
#pragma warning disable 612, 618
            modelBuilder
                .HasAnnotation("ProductVersion", "9.0.0-rc.2.24474.1")
                .HasAnnotation("Relational:MaxIdentifierLength", 63);

            NpgsqlModelBuilderExtensions.UseIdentityByDefaultColumns(modelBuilder);

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Hotel", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<string>("Address")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<double>("Area")
                        .HasColumnType("double precision");

                    b.Property<string>("Email")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<long>("OwnerId")
                        .HasColumnType("bigint");

                    b.Property<string>("Phone")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<string>("YearOpenedIn")
                        .IsRequired()
                        .HasColumnType("text");

                    b.HasKey("Id");

                    b.HasIndex("OwnerId");

                    b.ToTable("Hotel");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomFeature", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<string>("Description")
                        .HasColumnType("text");

                    b.Property<string>("Name")
                        .IsRequired()
                        .HasColumnType("text");

                    b.Property<long?>("RoomPropertiesId")
                        .HasColumnType("bigint");

                    b.HasKey("Id");

                    b.HasIndex("RoomPropertiesId");

                    b.ToTable("RoomFeatures");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomPriceRate", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<int>("PricePerNight")
                        .HasColumnType("integer");

                    b.Property<long>("PropertiesId")
                        .HasColumnType("bigint");

                    b.Property<DateTime>("StartDate")
                        .HasColumnType("timestamp with time zone");

                    b.HasKey("Id");

                    b.HasIndex("PropertiesId");

                    b.ToTable("RoomPriceRates");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<int>("Class")
                        .HasColumnType("integer");

                    b.Property<long>("HotelId")
                        .HasColumnType("bigint");

                    b.Property<int>("Size")
                        .HasColumnType("integer");

                    b.HasKey("Id");

                    b.HasIndex("HotelId");

                    b.ToTable("RoomProperties");
                });

            modelBuilder.Entity("Lab3.Entities.Hotel.People.Owner", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<string>("FullName")
                        .IsRequired()
                        .HasColumnType("text");

                    b.HasKey("Id");

                    b.ToTable("Owner");
                });

            modelBuilder.Entity("Lab3.Entities.Hotel.Rooms.Room", b =>
                {
                    b.Property<long>("Id")
                        .ValueGeneratedOnAdd()
                        .HasColumnType("bigint");

                    NpgsqlPropertyBuilderExtensions.UseIdentityByDefaultColumn(b.Property<long>("Id"));

                    b.Property<int>("Floor")
                        .HasColumnType("integer");

                    b.Property<long>("PropertiesId")
                        .HasColumnType("bigint");

                    b.Property<long>("RoomNumber")
                        .HasColumnType("bigint");

                    b.HasKey("Id");

                    b.HasIndex("PropertiesId");

                    b.ToTable("Rooms");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Hotel", b =>
                {
                    b.HasOne("Lab3.Entities.Hotel.People.Owner", "Owner")
                        .WithMany("Hotels")
                        .HasForeignKey("OwnerId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Owner");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomFeature", b =>
                {
                    b.HasOne("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", null)
                        .WithMany("Features")
                        .HasForeignKey("RoomPropertiesId");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomPriceRate", b =>
                {
                    b.HasOne("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", "Properties")
                        .WithMany()
                        .HasForeignKey("PropertiesId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Properties");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", b =>
                {
                    b.HasOne("Lab3.Data.Entities.Hotel.Hotel", "Hotel")
                        .WithMany()
                        .HasForeignKey("HotelId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Hotel");
                });

            modelBuilder.Entity("Lab3.Entities.Hotel.Rooms.Room", b =>
                {
                    b.HasOne("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", "Properties")
                        .WithMany()
                        .HasForeignKey("PropertiesId")
                        .OnDelete(DeleteBehavior.Cascade)
                        .IsRequired();

                    b.Navigation("Properties");
                });

            modelBuilder.Entity("Lab3.Data.Entities.Hotel.Rooms.RoomProperties", b =>
                {
                    b.Navigation("Features");
                });

            modelBuilder.Entity("Lab3.Entities.Hotel.People.Owner", b =>
                {
                    b.Navigation("Hotels");
                });
#pragma warning restore 612, 618
        }
    }
}